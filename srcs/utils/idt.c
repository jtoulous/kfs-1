#include "../kernel.h"

void init_idt(void) {
    for (int i = 0; i < 256; i++) {
        kernel.idt.cells[i].base_low = 0;
        kernel.idt.cells[i].selector = 0;
        kernel.idt.cells[i].zero = 0;
        kernel.idt.cells[i].flags = 0;
        kernel.idt.cells[i].base_high = 0;
    }

    unsigned int handler_addr = (unsigned int)keyboard_sig;
    kernel.idt.cells[33].base_low = handler_addr & 0xFFFF;
    kernel.idt.cells[33].selector = 8;
    kernel.idt.cells[33].zero = 0;
    kernel.idt.cells[33].flags = 142;
    kernel.idt.cells[33].base_high = (handler_addr >> 16) & 0xFFFF;

    t_idt_ptr idt_pointer;
    idt_pointer.limit = 2047;
    idt_pointer.base = (unsigned int)&kernel.idt;
    __asm__ volatile ("lidt %0" : : "m" (idt_pointer));

    init_pic();
    __asm__ volatile ("sti");
}

void init_pic(void) {
    outb(32, 17);
    outb(160, 17);
    outb(33, 32);
    outb(161, 40);
    outb(33, 4);
    outb(161, 2);
    outb(33, 1);
    outb(161, 1);
    outb(33, 253);
    outb(161, 255);
}