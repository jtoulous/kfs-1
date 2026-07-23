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



////////     Varz      ////////
extern volatile int key_pressed;
extern volatile int last_key;



////////     Structs      ////////
typedef struct {
    unsigned short base_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed)) t_idt_cell;

typedef struct {
    t_idt_cell    cells[256];
} __attribute__((packed)) t_idt_table;


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) t_idt_ptr;


typedef struct {
    //IDT table
    t_idt_table   idt;

    //Display
    char    *display;
    int     d_idx;
    char    d_color;

    //Command Line
    char    cmd_line[256];
    int     cmd_len;
} t_kernel;



////////     Fonctions      ////////
unsigned char inb(unsigned short);
void outb(unsigned short port, unsigned char val);

struct interrupt_frame;
__attribute__((interrupt))
void keyboard_sig(struct interrupt_frame *frame);

void enable_cursor_blink(void);
void move_cursor(int position);
char scan_to_ascii(unsigned char scan);

void    init_idt(t_kernel *kernel);
void    init_pic(void);

char *get_display(void);
void clear_display(t_kernel *);
void display_mandatory(t_kernel *);
void display_bonuses(t_kernel *);
void display_new_line(t_kernel *, int);
void display_cmd_line(t_kernel *);
void display_char(t_kernel *kernel, char c);
void display_char_n_color(t_kernel *kernel, char c, char color);

void handle_input(t_kernel *kernel, char input);


// for debug, to remove at the end
void tmp_pause(void);


#endif