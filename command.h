struct command {
    char** argv; // Includes the program name
};

struct command_list {
    struct command cmd;
    struct command_list* next;
};

void command_exec(struct command cmd);

void command_list_free(struct command_list* cmd_list);

struct command_list* command_list_make(char* str);
