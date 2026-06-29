extern   main
global   _start

MAGIC    equ 0x1BADB002
FLAGS    equ 0x00000003
CHECKSUM equ -(MAGIC + FLAGS)

section .text
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    _start:
        mov esp, stack_top
        call main
        cli

    hang:
        hlt
        jmp hang

section .bss
    align 16

    stack_bottom:
        resb 16384
    stack_top: