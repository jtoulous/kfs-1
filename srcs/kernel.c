#include "kernel.h"


volatile int key_pressed = 0;
volatile int last_key = 0;



void    init_kernel(t_kernel *kernel) {
    //Init kernel structure
    kernel->display = (char*)0xB8000;
    kernel->d_idx = 0;
    kernel->d_color = GREEN;

    kernel->cmd_line[0] = '\0';
    kernel->cmd_len = 0;
    
    enable_cursor_blink();
    clear_display(kernel);
    //init_idt();
    //init_keyboard();
}



//void    destroy_kernel(t_kernel *kernel) {
//    //Destroy kernel structure
//    kernel->cmd_line = NULL;
//}



// THE KERNEL
void main(void) {
    t_kernel    kernel;  

    // Start kernel
    init_kernel(&kernel);
    
    // Mandatory
    display_mandatory(&kernel);
    
    // Bonuses
    display_bonuses(&kernel);

    while (1) {
        display_cmd_line(&kernel);

        while (1) {
            if (key_pressed == 1) {
                char input = scan_to_ascii((unsigned char)last_key);
                key_pressed = 0;
                last_key = 0;
            
                handle_input(&kernel, input);
                if (input == '\n') {
                    // execute_command(kernel->cmd_line)
                    // reset buffer
                    break;
                }
            }
        }
    }

    //destroy_kernel(&kernel);
}