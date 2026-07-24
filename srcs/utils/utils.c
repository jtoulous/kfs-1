#include "../kernel.h"

void tmp_pause(void) {
    __asm__ volatile ("hlt");
}

unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void enable_cursor_blink(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x0E);
    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x0F);
}

void move_cursor(int position) {
    unsigned short pos = position / 2;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}


void printf(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        display_char(str[i]);
    }
}


char scan_to_ascii(unsigned char scan) {
    char table[128] = {
        [0x00] = 0,     // erreur
        [0x01] = 0,     // Escape
        [0x02] = '1',
        [0x03] = '2',
        [0x04] = '3',
        [0x05] = '4',
        [0x06] = '5',
        [0x07] = '6',
        [0x08] = '7',
        [0x09] = '8',
        [0x0A] = '9',
        [0x0B] = '0',
        [0x0C] = '-',
        [0x0D] = '=',
        [0x0E] = '\b',     // Backspace
        [0x0F] = 0,     // Tab
        [0x10] = 'q',
        [0x11] = 'w',
        [0x12] = 'e',
        [0x13] = 'r',
        [0x14] = 't',
        [0x15] = 'y',
        [0x16] = 'u',
        [0x17] = 'i',
        [0x18] = 'o',
        [0x19] = 'p',
        [0x1A] = '[',
        [0x1B] = ']',
        [0x1C] = '\n',   // Entree
        [0x1D] = 0,     // Ctrl
        [0x1E] = 'a',
        [0x1F] = 's',
        [0x20] = 'd',
        [0x21] = 'f',
        [0x22] = 'g',
        [0x23] = 'h',
        [0x24] = 'j',
        [0x25] = 'k',
        [0x26] = 'l',
        [0x27] = ';',
        [0x28] = '\'',
        [0x29] = '`',
        [0x2A] = 0,     // Shift gauche
        [0x2B] = '\\',
        [0x2C] = 'z',
        [0x2D] = 'x',
        [0x2E] = 'c',
        [0x2F] = 'v',
        [0x30] = 'b',
        [0x31] = 'n',
        [0x32] = 'm',
        [0x33] = ',',
        [0x34] = '.',
        [0x35] = '/',
        [0x36] = 0,     // Shift droit
        [0x37] = '*',   // (clavier num)
        [0x38] = 0,     // Alt
        [0x39] = ' ',
    };
    if (scan < 128) return table[scan];
    return 0;
}