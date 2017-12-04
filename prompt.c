#include "prompt.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_prompt() {
  char current_d[100];
  getcwd(current_d, sizeof(current_d));

  printf("%s$ ", current_d);
}