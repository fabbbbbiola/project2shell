#include "command.h"

char** separate_on_space(char* input, size_t* sepv_size) {
    size_t substr_count = 0;
    for (; input != NULL; substr_count++) {
        strsep(&input, " ");
    }

    char** sepv = malloc(substr_count);
    *sepv_size = substr_count;

    size_t i = 0;
    char* cur_substr = input;

    for (; i < substr_count; i++) {
        sepv[i] = cur_substr;
        cur_substr += strlen(cur_substr) + 1;
    }

    return sepv;
}

void exec_command(command* cmdp) {
    execvp(cmdp->argv[0], cmdp->argv);
}

command_list make_command_vector(char* input) {
    size_t sepv_size;
    char** sepv = separate_on_space(input, &sepv_size);

    command_list cmdl = new_command_list();
    
    size_t i = 0;
    for (; i < sepv_size; i++) {
        char* cur_substr = sepv[i];
        
    }

    free(sepv);
}
