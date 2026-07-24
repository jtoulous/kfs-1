#include "../kernel.h"


__attribute__((interrupt))
void keyboard_sig(struct interrupt_frame *frame) {
    (void)frame;
    kernel.last_key = inb(0x60);
    kernel.key_pressed = 1;
    outb(0x20, 0x20);
}