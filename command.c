#include "command.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

// If the 'num_substrings' pointer is NULL, then this function does not write to
// the pointer. Instead, it NULL-terminates the return value.
char** split_on(char* needle, char* input, size_t* num_substrings) {
    size_t substring_count = 0;
    char* substring = input;
    for (; substring != NULL; substring_count++) {
        strsep(&substring, needle);
    }

    char** substrings;
    if (num_substrings == NULL) {
        substrings = malloc(substring_count + 1);
        substrings[substring_count] = NULL;
    } else {
        substrings = malloc(substring_count);
        *num_substrings = substring_count;
    }

    size_t i = 0;
    char* current_substring = input;

    for (; i < substring_count; i++) {
        substrings[i] = current_substring;
        current_substring += strlen(current_substring) + 1;
    }

    return substrings;
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
        printf("%s\n", to_print);
    } else {
        if (fork() == 0) {
            execvp(cmd.argv[0], cmd.argv);
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

    size_t i = 0;
    for (; i < num_commands; i++) {
        char* cmd_string = cmd_strings[i];
        struct command cmd;
        cmd.argv = split_on(" ", cmd_string, NULL);
        cmd_list = command_list_insert_front(cmd_list, cmd);
    }

    free(cmd_strings);
    return cmd_list;
}
