struct command {
    char** argv; // Includes the program name
};

struct command_list {
    command item;
    command_list* next;
};

void exec_command(command* cmdp);

command_list* make_command_list(char* str);

command_list* empty_command_list();

command_list* insert(command_list* cmdl, command* command);
