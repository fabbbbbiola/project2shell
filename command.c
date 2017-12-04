#include "command.h"

#include <stddef.h>

// If the 'num_substrings' pointer is NULL, then this function does not write to
// the pointer. Instead, it NULL-terminates the return value.
char** split_on(char* needle, char* input, size_t* num_substrings) {
    size_t substring_count = 0;
    for (; input != NULL; substring_count++) {
        strsep(&input, needle);
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
    execvp(cmd.argv[0], cmd.argv);
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
        command_list_insert_front(cmd_list, cmd);
    }

    free(cmd_strings);
    return cmd_list;
}
