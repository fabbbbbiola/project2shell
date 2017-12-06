# shell

by James Ko and Fabiola Radosav

## Features

- Parses and executes commands
- Prints current working directory
- Using semicolons to separate commands works
- Redirection with <, >
- Pipes work

## Attempted

- To split commands on quotes and semicolons
- To print a current working directory prompt in linux format. Couldn't figure out how to separate it so that the "/"s and the unnecessary directory info wouldn't print.

## Headers

command.h

```c
struct command {
  char* in_from_file; // <
  char** in_from_program; // Left end of |
  char* out_to_file; // >
    char** argv; // Includes the program name
};

struct command_list {
    struct command cmd;
    struct command_list* next;
};

void command_exec(struct command cmd);

void command_list_free(struct command_list* cmd_list);

struct command_list* command_list_make(char* str);
```

input.h

```c
char* get_input(void);
```

input\_handler.h

```c
void handle_input(char* input);
```

prompt.h

```c
void print_prompt();
```
