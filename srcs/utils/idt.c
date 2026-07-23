#include "../kernel.h"


void init_idt(t_kernel *kernel) {
    // set to 0
    for(int i = 0; i < 256; i++) {
        kernel->idt.cells[i].base_low = 0;
        kernel->idt.cells[i].selector = 0;
        kernel->idt.cells[i].zero = 0;
        kernel->idt.cells[i].flags = 0;
        kernel->idt.cells[i].base_high = 0;
    }

    // Config 33 for keyboard
    unsigned int handler_addr = (unsigned int)keyboard_sig;
    kernel->idt.cells[33].base_low = handler_addr & 0xFFFF;
    kernel->idt.cells[33].selector = 8;
    kernel->idt.cells[33].zero = 0;
    kernel->idt.cells[33].flags = 142;
    kernel->idt.cells[33].base_high = (handler_addr >> 16) & 0xFFFF;

    // Set pointeur to IDT and load with lidt
    t_idt_ptr idt_pointer;
    idt_pointer.limit = 2047;
    idt_pointer.base = (unsigned int)&kernel->idt;
    __asm__ volatile ("lidt %0" : : "m" (idt_pointer));

    // Init PIC (doit être fait AVANT sti)
    init_pic();

    // Activate STI
    __asm__ volatile ("sti");
}

void    init_pic(void) {
    // ICW1
    outb(32, 17);
    outb(160, 17);

    // ICW2
    outb(33, 32);
    outb(161, 40);

    // ICW3
    outb(33, 4);
    outb(161, 2);

    // ICW4
    outb(33, 1);
    outb(161, 1);

    // Masques
    outb(33, 253);   // IRQ1 (clavier)
    outb(161, 255);  // désactive tout le reste
}