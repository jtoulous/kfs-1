#ifndef KERNEL_H
#define KERNEL_H

// Couleurs
#define COLORCODE(fg, bg) (((bg) << 4) | (fg))
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

#define NULL ((void *)0)



typedef struct {
    char    *display;
    int     d_idx;
    char    d_color;

    char    *cmd_line;
    char    *history;
} t_kernel;


void enable_cursor_blink(void);
void move_cursor(int position);

char *get_display(void);
void clear_display(t_kernel *);
void display_mandatory(t_kernel *);
void display_bonuses(t_kernel *);
void display_new_line(t_kernel *, int);
void display_cmd_line(t_kernel *);

// for debug, to remove at the end
void tmp_pause(void);

#endif