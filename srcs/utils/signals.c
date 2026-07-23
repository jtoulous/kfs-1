#include "../kernel.h"


__attribute__((interrupt))
void keyboard_sig(struct interrupt_frame *frame) {
    (void)frame;
    last_key = inb(0x60);
    key_pressed = 1;
    outb(0x20, 0x20);
}