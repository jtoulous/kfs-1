#include "../kernel.h"



void tmp_pause(void) {
    __asm__ volatile ("hlt");
}


void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


void disable_default_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x00);
}