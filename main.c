#include "input.h"
#include "input_handler.h"
#include "prompt.h"
#include "dirent.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

void print_prompt(){

  //chdir()
  char* current_d[100];
  size_t size = 100;
  
  char* dir_name = getcwd(*current_d, size);
  printf("%s", dir_name);
  
  /*
  DIR * d = opendir(".");
  struct dirent * entry = readdir(d);
  d = opendir(".");
  entry = readdir(d);

  if(entry->d_type == DT_DIR){
    printf("shell:%s$\n", entry->d_name);
  }

    user name :~$ or username:~/dir$
  if (in user directory but not in any subdirectories){
    printf(“%s~$\t”, user);
  }
  if (in a specific sub directory:){
    printf(“%s :~%s$\t “, user, dirname  );
  }
  */

}


int main() {
    while (1) {
        print_prompt();
        char* str = get_input();
        handle_input(str);
    }

    return 0;
}
