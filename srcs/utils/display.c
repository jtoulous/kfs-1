#include "../kernel.h"


//////////////////////////////////////////////////////
//////                  UTILS                    /////

char *get_display(void) {
    return (char*)0xB8000;
}


void clear_display(int *d_idx) {
    char *display = get_display();
    
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        display[i] = ' ';
        display[i + 1] = WHITE;
    }
    *d_idx = 0;
}

void display_new_line(int *d_idx, int nb) {
    for(int i = 0; i < nb; i++){    
        int line = *d_idx / 160;
        int next_line = line + 1;

        *d_idx = next_line * 160;
    }
}


//////////////////////////////////////////////////////
//////                  CURSOR                   /////


void display_cursor(int *d_idx) {
    char *display = get_display();

    display[*d_idx] = '_';
    display[*d_idx + 1] = COLORCODE(WHITE, BLACK);
}

void display_cmd_line(int *d_idx) {
    char *display = get_display();

    display_new_line(d_idx, 1);

    display[*d_idx] = '>';
    display[*d_idx + 1] = COLORCODE(WHITE, BLACK);

    *d_idx += 2;
}



//////////////////////////////////////////////////////
//////                MANDATORY                  /////

void display_mandatory(int *d_idx) {
    char *display = get_display();
    char *mandatory_hdr = "==========  MANDATORY  ==========\n=================================\n              42                 ";
    
    display_new_line(d_idx, 1);

    for (int i = 0; mandatory_hdr[i] != '\0'; i++) {
        char c = mandatory_hdr[i];
        char color;
        
        if (c == '=') {
            color = COLORCODE(WHITE, BLACK);
        } 
        else if (c == ' ') {
            color = COLORCODE(WHITE, BLACK);
        }
        else if (c == '\n') {
            display_new_line(d_idx, 1);
            continue;
        }
        else {
            color = COLORCODE(WHITE, BLACK);
        }
        
        display[*d_idx] = c;
        display[*d_idx + 1] = color;
        *d_idx += 2;
    }
}


void display_bonuses(int *d_idx) {
    char *display = get_display();
    char *bonus_hdr = "===========  BONUSES  ==========\n=================================\n";
    
    display_new_line(d_idx, 5);

    for (int i = 0; bonus_hdr[i] != '\0'; i++) {
        char c = bonus_hdr[i];
        char color;
        
        if (c == '=') {
            color = COLORCODE(GREEN, BLACK);
        } 
        else if (c == ' ') {
            color = COLORCODE(WHITE, BLACK);
        }
        else if (c == '\n') {
            display_new_line(d_idx, 1);
            continue;
        }
        else {
            color = COLORCODE(GREEN, BLACK);
        }
        
        display[*d_idx] = c;
        display[*d_idx + 1] = color;
        *d_idx += 2;
    }

    display_new_line(d_idx, 1);
}

