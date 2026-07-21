#include "../kernel.h"


//////////////////////////////////////////////////////
//////                  UTILS                    /////

char *get_display(void) {
    return (char*)0xB8000;
}


void clear_display(t_kernel *kernel) {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        kernel->display[i] = ' ';
        kernel->display[i + 1] = WHITE;
    }
    kernel->d_idx = 0;
    move_cursor(0);
}


void display_new_line(t_kernel *kernel, int nb) {
    for (int i = 0; i < nb; i++) {
        int line = kernel->d_idx / 160;
        int next_line = line + 1;
        kernel->d_idx = next_line * 160;
    }
    move_cursor(kernel->d_idx);
}

void display_char_n_color(t_kernel *kernel, char c, char color) {
    if (c != '\n') {
        kernel->display[kernel->d_idx] = c;
        kernel->display[kernel->d_idx + 1] = COLORCODE(color, BLACK);
        kernel->d_idx += 2;
        move_cursor(kernel->d_idx);
    }
    else if (c == '\n') {
        display_new_line(kernel, 1);
    }
}


void display_char(t_kernel *kernel, char c) {
    if (c != '\n') {
        kernel->display[kernel->d_idx] = c;
        kernel->display[kernel->d_idx + 1] = COLORCODE(kernel->d_color, BLACK);
        kernel->d_idx += 2;
        move_cursor(kernel->d_idx);
    }
    else if (c == '\n') {
        display_new_line(kernel, 1);
    }
}


//////////////////////////////////////////////////////
//////                  CURSOR                   /////


void display_cmd_line(t_kernel *kernel) {
    char *cmd_line = "kfs-1> ";

    display_new_line(kernel, 1);

    for (int i = 0; cmd_line[i] != '\0'; i++) {
        display_char(kernel, cmd_line[i]);
    }
}



//////////////////////////////////////////////////////
//////                MANDATORY                  /////

void display_mandatory(t_kernel *kernel) {
    char *mandatory_hdr = "==========  MANDATORY  ==========\n=================================\n              42                 ";
    
    display_new_line(kernel, 1);

    for (int i = 0; mandatory_hdr[i] != '\0'; i++) {
        display_char_n_color(kernel, mandatory_hdr[i], WHITE);
    }
}


void display_bonuses(t_kernel *kernel) {
    char *bonus_hdr = "===========  BONUSES  ==========\n================================\n";
    
    display_new_line(kernel, 5);

    for (int i = 0; bonus_hdr[i] != '\0'; i++) {
        display_char(kernel, bonus_hdr[i]);
    }

    display_new_line(kernel, 1);
}