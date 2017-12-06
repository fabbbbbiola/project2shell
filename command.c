#include "command.h"

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

struct redirect_state {
  int orig_in_fd;
  int orig_out_fd;
  int new_in_fd;
  int new_out_fd;
};

// If the 'num_substrings' pointer is NULL, then this function does not write to
// the pointer. Instead, it NULL-terminates the return value.
char** split_on(char* needle, char* input, size_t* num_substrings) {
    size_t needle_len = strlen(needle);

    size_t substring_count = 0;
    char* substring = input;

    for (; substring != NULL; substring_count++) {
        // Don't create empty substrings from duplicate occurrences of needle.
        while (strncmp(needle, substring, needle_len) == 0) {
            substring += needle_len;
        }

	// If we're at the end of the string due to duplicate occurrences of
	// needle, avoid creating an empty string at the end.
	if (substring[0] == '\0') {
	    break;
	}

        strsep(&substring, needle);
    }

    char** substrings;
    if (num_substrings == NULL) {
        substrings = malloc((substring_count + 1) * sizeof(char*));
        substrings[substring_count] = NULL;
    } else {
        substrings = malloc(substring_count * sizeof(char*));
        *num_substrings = substring_count;
    }

    size_t i = 0;
    char* current_substring = input;

    for (; i < substring_count; i++) {
        // Skip empty substrings.
        while (strncmp(needle, current_substring, needle_len) == 0) {
            current_substring += needle_len;
        }

        substrings[i] = current_substring;
        current_substring += strlen(current_substring) + needle_len;
    }

    return substrings;
}

struct redirect_state set_in_out_from_command(struct command cmd) { 
  struct redirect_state state;
  
  if (cmd.in_from_file != NULL) {
    state.orig_in_fd = dup(STDIN_FILENO);
    state.new_in_fd = open(cmd.in_from_file, O_CREAT | O_RDONLY, 0644);
    dup2(state.new_in_fd, STDIN_FILENO);
  } else if (cmd.in_from_program != NULL) {
      int fds[2];
      pipe(fds);

      if (fork() == 0) {
        // We're the child. Execute the command that's having its output piped.
        // TODO: Handle echo/cd here.
        close(fds[READ_PIPE]);
        dup2(fds[WRITE_PIPE], STDOUT_FILENO);
        execvp(cmd.in_from_program[0], cmd.in_from_program);
      } else {
        // We're the parent. Execute the command that's taking input from the pipe.
        close(fds[WRITE_PIPE]);
        state.orig_in_fd = dup(STDIN_FILENO);
        state.new_in_fd = fds[READ_PIPE];
        dup2(state.new_in_fd, STDIN_FILENO);
      }
  } else {
    state.orig_in_fd = -1;
    state.new_in_fd = -1;
  }

  if (cmd.out_to_file != NULL) {
    state.orig_out_fd = dup(STDOUT_FILENO);
    state.new_out_fd = open(cmd.out_to_file, O_CREAT | O_WRONLY, 0644);
    dup2(state.new_out_fd, STDOUT_FILENO);
  } else {
    state.orig_out_fd = -1;
    state.new_out_fd = -1;
  }

  return state;
}

void unset_in_out_from_command(struct redirect_state state) {
  if (state.new_in_fd != -1) {
    close(state.new_in_fd);
    dup2(state.orig_in_fd, STDIN_FILENO);
    close(state.orig_in_fd);
  }

  if (state.new_out_fd != -1) {
    close(state.new_out_fd);
    dup2(state.orig_out_fd, STDOUT_FILENO);
    close(state.orig_out_fd);
  }
}

// Note: The array should be null-terminated.
// Returns NULL if we can't find the word.
char** find_word(char* word, char** array) {
  size_t word_len = strlen(word);
  
  size_t i = 0;
  for (; array[i] != NULL; i++) {
    if (strncmp(word, array[i], word_len) == 0) {
      return array + i;
    }
  }

  return NULL;
}

void command_exec(struct command cmd) {
    char* program_name = cmd.argv[0];
    if (strcmp(program_name, "cd") == 0) {
        char* target = cmd.argv[1] != NULL ? cmd.argv[1] : getenv("HOME");
        chdir(target);
    } else if (strcmp(program_name, "echo") == 0) {
        char to_print[256] = "";
        if (cmd.argv[1] != NULL) {
            strcat(to_print, cmd.argv[1]);
            size_t i = 2;
            for (; cmd.argv[i] != NULL; i++) {
                strcat(to_print, " ");
                strcat(to_print, cmd.argv[i]);
            }
        }
	struct redirect_state state = set_in_out_from_command(cmd);
        printf("%s\n", to_print);
	unset_in_out_from_command(state);
    } else if (strcmp(program_name, "exit") == 0) {
        exit(0);
    } else {
        if (fork() == 0) {
            struct redirect_state state = set_in_out_from_command(cmd);
            execvp(cmd.argv[0], cmd.argv);
            unset_in_out_from_command(state);
        } else {
            int wstatus;
            wait(&wstatus);
        }
    }
}

void command_list_free(struct command_list* cmd_list) {
    struct command_list* current = cmd_list;
    while (current != NULL) {
        struct command_list* prev = current;
        current = current->next;
        free(prev->cmd.argv);
        free(prev);
    }
}

struct command_list* command_list_insert_front(struct command_list* cmd_list, struct command cmd) {
    struct command_list* new_list = malloc(sizeof(struct command_list));
    new_list->cmd = cmd;
    new_list->next = cmd_list;
    return new_list;
}

struct command_list* command_list_make(char* str) {
    size_t num_commands;
    char** cmd_strings = split_on(";", str, &num_commands);

    struct command_list* cmd_list = NULL;

    size_t i = num_commands;
    for (; i > 0; i--) {
        char* cmd_string = cmd_strings[i - 1];
        struct command cmd;
        cmd.argv = split_on(" ", cmd_string, NULL);
	
	char** in_ptr = find_word("<", cmd.argv);
	if (in_ptr != NULL && in_ptr[1] != NULL) {
	  cmd.in_from_file = in_ptr[1];
	  // Null-terminate the array earlier '< file' isn't included in the argv passed to execvp().
	  in_ptr[0] = NULL;
	  in_ptr[1] = NULL;
	} else {
	  cmd.in_from_file = NULL;
	}

	char** out_ptr = find_word(">", cmd.argv);
	if (out_ptr != NULL && out_ptr[1] != NULL) {
	  cmd.out_to_file = out_ptr[1];
	  // Null-terminate the array earlier '< file' isn't included in the argv passed to execvp().
	  out_ptr[0] = NULL;
	  out_ptr[1] = NULL;
	} else {
	  cmd.out_to_file = NULL;
    }
    
    char** pipe_ptr = find_word("|", cmd.argv);
    if (pipe_ptr != NULL && pipe_ptr[1] != NULL) {
        // Set in_from_program to the original argv.
        // Null-terminate it by setting pipe_ptr to NULL.
        // Point argv to the arguments past the pipe.
        cmd.in_from_program = cmd.argv;
        pipe_ptr[0] = NULL;
        cmd.argv = pipe_ptr + 1;
    } else {
        cmd.in_from_program = NULL;
    }
	
        cmd_list = command_list_insert_front(cmd_list, cmd);
    }

    free(cmd_strings);
    return cmd_list;
}
