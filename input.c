#include "input.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_input() {
  char buffer[256];
  if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    return NULL;
  }

  size_t size = strlen(buffer);
  if (buffer[size - 1] == '\n') {
    // Exclude the newline.
    size--;
  }

  char* temp = malloc(size + 1);
  strncpy(temp, buffer, size);
  temp[size] = '\0';
  return temp;
}

 
