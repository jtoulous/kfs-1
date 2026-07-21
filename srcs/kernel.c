#include "kernel.h"



void    init_kernel(t_kernel *kernel) {
    //Init kernel structure
    kernel->display = (char*)0xB8000;
    kernel->d_idx = 0;
    kernel->d_color = GREEN;

    kernel->cmd_line = NULL;
    kernel->history = NULL;

    disable_default_cursor();
    clear_display(kernel);
    //init_idt();
    //init_keyboard();
}



void    destroy_kernel(t_kernel *kernel) {
    //Destroy kernel structure
    kernel->cmd_line = NULL;
    kernel->history = NULL;
}



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
        display_cursor(&kernel);
        
        tmp_pause();

        //await_input(kernel, input);
        //execute_input(input);
        //reset_input(kernel, input);
    }

    //destroy_kernel(&kernel);
}