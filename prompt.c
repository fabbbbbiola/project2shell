#include "prompt.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_prompt() {
  char* current_d[100];
  char* substr[100];
  char* dir_name = getcwd(*current_d, sizeof(char));

  printf("%s$ ", dir_name);
}