#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* get_input(){
  int bufsz = 1000;
  int pos = 0;
  char *buff = malloc(sizeof(char) * bufsz);
  char c;

  c = getchar();
  //strcpy(buff, c);

  while (buff){
    if (c == EOF){
      return buff;
    }
    else {
      buff[pos] = c;
    }
    pos++;
    
    if (pos >= bufsz){
      bufsz += 1000;
      buff = (char*)realloc(buff, bufsz);
    }
  }
  
}
