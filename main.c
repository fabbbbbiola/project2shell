#include "input.h"
#include "input_handler.h"
#include "prompt.h"
#include "dirent.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

void print_prompt(){

  char* current_d[100];
  char* substr[100];
  char* dir_name = getcwd(*current_d, sizeof(char));

  printf("%s$\n", dir_name);

}

int main() {
    while (1) {
        print_prompt();
        char* str = get_input();
        handle_input(str);
    }

    return 0;
}
