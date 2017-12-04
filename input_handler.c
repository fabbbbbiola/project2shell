#include "command.h"

#include <stddef.h>

void handle_input(char* input) {
    struct command_list* cmd_list = command_list_make(input);

    struct command_list* current = cmd_list;
    for (; current != NULL; current = current->next) {
        command_exec(current->cmd);
    }

    free_command_list(cmd_list);
    free(input);
}
