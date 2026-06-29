#include "kernel.h"

char *get_video_window(void) {
    return (char*)0xB8000;
}

void clear(void) {
    char *video = get_video_window();
    
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = WHITE;
    }
}

void print_42(void) {
    char *video = get_video_window();
    
    video[0] = '4';
    video[1] = COLORCODE(GREEN, BLACK);
    video[2] = '2';
    video[3] = COLORCODE(GREEN, BLACK);
}





// LE NOYAU
void main(void) {
    clear();
    print_42();
}