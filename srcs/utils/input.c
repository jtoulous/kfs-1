#include "../kernel.h"


void handle_input(t_kernel *kernel, char input) {
    if (input == '\n') {
        display_char(kernel, '\n');
        return;
    }
    
    if (kernel->cmd_len < 255) {
        kernel->cmd_line[kernel->cmd_len++] = input;
        kernel->cmd_line[kernel->cmd_len] = '\0';
        display_char(kernel, input);
    }
}





//void manage_input(int *d_idx, char *input){
//
//}
//
//
//
//void execute_input(int *d_idx, char *input){
//
//}
//
//
//
//void reset_input(int *d_idx, char *input){
//
//}