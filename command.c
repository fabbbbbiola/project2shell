#include "command.h"

char** separate_on(char* needle, char* input, size_t* sepv_size) {
    size_t substr_count = 0;
    for (; input != NULL; substr_count++) {
        strsep(&input, needle);
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

void exec_command(command cmd) {
    execvp(cmd.argv[0], cmd.argv);
}

command_list* make_list_command(char* str) {
    size_t sepv_size;
    // Contains the input split on " "
    char** sep_vec = separate_on(" ", input, &sepv_size);

    command_list* cmd_list = NULL;
    command current;
    current.argv = NULL;

    string_list* argv_list = NULL;
    
    size_t i = 0;
    for (; i < sepv_size; i++) {
        char* current_substr = sep_vec[i];
        // TODO: Change to handle quotes (" and '), and semicolons (;)
	insert_front_string(&argv_list, current_substr);
    }

    current.argv = to_array_string(argv_list);
   
    free_list_string(argv_list);
    free(sepv);
}
