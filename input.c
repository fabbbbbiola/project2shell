#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

char* get_input(void){
  char str[256];
  int size = strlen(str);
  int i;
  char* temp = (char*)malloc(size + 1);

  fgets(str, sizeof(str), stdin);

  if (fgets(str, sizeof(str), stdin) == NULL){
    printf("error: %s\n", strerror(errno));
  }
  
  for (i = 0; i < size; i++){
    temp[i] = str[i];
  }
  temp[size] = '\0';

  return temp;
  
}

 
