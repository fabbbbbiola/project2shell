#include "input.h"
#include "input_handler.h"
#include "prompt.h"

int main() {
    while (1) {
        print_prompt();
        char* str = get_input();
        handle_input(str);
    }

    return 0;
}
