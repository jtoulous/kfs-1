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

#define CMD_MAX_SIZE 256


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
    // IDT table
    t_idt_table   idt;

    // Display
    char    *display;
    int     d_idx;
    char    d_color;

    // Command Line
    char    cmd_line[CMD_MAX_SIZE];
    int     cmd_len;

    // Keyboard
    int     key_pressed;
    int     last_key;
} t_kernel;

////////     Varz      ////////
extern volatile t_kernel kernel;

////////     Fonctions      ////////
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char val);

struct interrupt_frame;
__attribute__((interrupt))
void keyboard_sig(struct interrupt_frame *frame);

void enable_cursor_blink(void);
void move_cursor(int position);
char scan_to_ascii(unsigned char scan);

void init_idt(void);
void init_pic(void);

char *get_display(void);
void clear_display(void);
void display_mandatory(void);
void display_bonuses(void);
void display_new_line(int nb);
void display_cmd_line(void);
void display_char(char c);
void display_char_n_color(char c, char color);
void printf(char *str);

int handle_input(char input);
void handle_backspace(void);
void handle_regular_char(char input);

void tmp_pause(void);

#endif