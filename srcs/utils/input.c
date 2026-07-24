#include "../kernel.h"



int handle_input(char input) {
    if (input == '\n') {
        //execute input
        return 1;
    }
    else if (input == '\b') {
        handle_backspace();
    }
    else {
        handle_regular_char(input);
    }

    return 0;
}


void handle_regular_char(char input){
    if (kernel.cmd_len < 255) {
        kernel.cmd_line[kernel.cmd_len] = input;
        kernel.cmd_line[kernel.cmd_len + 1] = '\0';
        kernel.cmd_len++;

        display_char(input);
    }
}

void handle_backspace(void) {
    if (kernel.cmd_len > 0) {
        kernel.cmd_len--;
        kernel.cmd_line[kernel.cmd_len] = '\0';
        
        // effacer l'affichage
        kernel.d_idx -= 2;
        display_char(' ');
        kernel.d_idx -= 2;
        
        move_cursor(kernel.d_idx);
    }
}