#include "../kernel.h"



void keyboard_sig(void){
    last_key = inb(0x60);
    key_pressed = 1;
    outb(0x20, 0x20);
}