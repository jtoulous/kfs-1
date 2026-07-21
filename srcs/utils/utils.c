#include "../kernel.h"



void tmp_pause(void) {
    __asm__ volatile ("hlt");
}


void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void enable_cursor_blink(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x0E);   // start scanline = 14
    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x0F);   // end scanline = 15
}


void move_cursor(int position) {
    unsigned short pos = position / 2;
    
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}