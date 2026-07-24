#include "kernel.h"

volatile t_kernel kernel;

void init_kernel(void) {
    // Init IDT
    init_idt();

    // Init Display
    kernel.display = (char*)0xB8000;
    kernel.d_idx = 0;
    kernel.d_color = GREEN;
    clear_display();
    enable_cursor_blink();

    // Init Command Line
    kernel.cmd_line[0] = '\0';
    kernel.cmd_len = 0;

    // Init Keyboard vars
    kernel.key_pressed = 0;
    kernel.last_key = 0;
}



void main(void) {
    init_kernel();

    display_mandatory();
    display_bonuses();

    while (1) {
        display_cmd_line();

        while (1) {
            if (kernel.key_pressed) {
                char input = scan_to_ascii((unsigned char)kernel.last_key);
                kernel.key_pressed = 0;
                kernel.last_key = 0;

                if (input != '\0') {
                    if (handle_input(input) == 1) {
                        // Commande reçue
                        // execute_command();
                        // reset cmd_line / cmd_len
                        break;
                    }
                }
            }
        }
        
    }
}