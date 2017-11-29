struct command {
    char** argv; // Includes the program name
};

struct command_list {
    command cmd;
    command_list* next;
};

void exec_command(command cmd);

command_list* make_list_command(char* str);
