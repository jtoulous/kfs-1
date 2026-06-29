#ifndef KERNEL_H
#define KERNEL_H

// Couleurs
#define BLACK   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define BROWN   0x6
#define LGRAY   0x7
#define DGRAY   0x8
#define LBLUE   0x9
#define LGREEN  0xA
#define LCYAN   0xB
#define LRED    0xC
#define LMAGENTA 0xD
#define YELLOW  0xE
#define WHITE   0xF

// Macro pour créer un attribut
#define COLORCODE(fg, bg) (((bg) << 4) | (fg))

#endif