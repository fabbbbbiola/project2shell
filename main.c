#include "input.h"
#include "input_handler.h"
#include "prompt.h"

#include <stddef.h>

int main() {
    // TODO: Handle Ctrl+C by exiting the program instead of the terminal itself.
    // TODO: Fix memory leaks.
    while (1) {
        print_prompt();
        char* str = get_input();
        if (str == NULL) {
            break;
        }
        handle_input(str);
    }

    return 0;
}
