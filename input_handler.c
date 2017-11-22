#include "command.h"

void handle_input(char* input) {
    command* cmdv = make_command_vector(input);

    command* cmdp;
    for (cmdp = cmdv; cmdp != NULL; cmdp++) {
        exec_command(cmdp);
    }

    free(input);
}
