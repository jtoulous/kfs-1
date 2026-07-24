#include "../kernel.h"

#define VGA_SIZE (80 * 25 * 2)

char *get_display(void) {
    return (char*)0xB8000;
}

void clear_display(void) {
    for (int i = 0; i < VGA_SIZE; i += 2) {
        kernel.display[i] = ' ';
        kernel.display[i + 1] = WHITE;
    }
    kernel.d_idx = 0;
    move_cursor(0);
}

void display_new_line(int nb) {
    for (int i = 0; i < nb; i++) {
        int line = kernel.d_idx / 160;
        int next_line = line + 1;
        kernel.d_idx = next_line * 160;
    }
    if (kernel.d_idx >= VGA_SIZE) {
        clear_display();
    }
    move_cursor(kernel.d_idx);
}

void display_char_n_color(char c, char color) {
    if (c != '\n') {
        kernel.display[kernel.d_idx] = c;
        kernel.display[kernel.d_idx + 1] = COLORCODE(color, BLACK);
        kernel.d_idx += 2;
        if (kernel.d_idx >= VGA_SIZE) {
            clear_display();
        }
        move_cursor(kernel.d_idx);
    } else {
        display_new_line(1);
    }
}

void display_char(char c) {
    if (c != '\n') {
        kernel.display[kernel.d_idx] = c;
        kernel.display[kernel.d_idx + 1] = COLORCODE(kernel.d_color, BLACK);
        kernel.d_idx += 2;
        if (kernel.d_idx >= VGA_SIZE) {
            clear_display();
        }
        move_cursor(kernel.d_idx);
    } else {
        display_new_line(1);
    }
}

void display_cmd_line(void) {
    char *cmd_line = "kfs-1> ";
    
    display_new_line(1);
    for (int i = 0; cmd_line[i] != '\0'; i++) {
        display_char(cmd_line[i]);
    }
    for (int i = 0; i < CMD_MAX_SIZE; i++)
        kernel.cmd_line[i] = '\0';
    kernel.cmd_len = 0;
}

void display_mandatory(void) {
    char *mandatory_hdr = "==========  MANDATORY  ==========\n=================================\n              42                 ";
    display_new_line(1);
    for (int i = 0; mandatory_hdr[i] != '\0'; i++) {
        display_char_n_color(mandatory_hdr[i], WHITE);
    }
}

void display_bonuses(void) {
    char *bonus_hdr = "===========  BONUSES  ==========\n================================\n";
    display_new_line(5);
    for (int i = 0; bonus_hdr[i] != '\0'; i++) {
        display_char(bonus_hdr[i]);
    }
    display_new_line(1);
}