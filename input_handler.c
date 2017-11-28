#include "command.h"

void handle_input(char* input) {
    command_list* cmd_list = make_command_list(input);

    command_list* current;
    for (current = cmd_list; current != NULL; current = current->next)
        exec_command(current->cmd);
    }

    free_command_list(cmd_list);
    free(input);
}
