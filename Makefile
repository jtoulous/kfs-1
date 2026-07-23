# Compilateurs et flags
ASM = nasm
CC = gcc
LD = ld

# Flags
ASM_FLAGS = -f elf32
CC_FLAGS = -m32 -ffreestanding -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -fno-stack-protector -mgeneral-regs-only
LD_FLAGS = -m elf_i386 -T srcs/linker.ld

# Fichiers sources
ASM_SOURCES = srcs/boot.s
C_SOURCES = srcs/kernel.c srcs/utils/display.c srcs/utils/utils.c srcs/utils/input.c srcs/utils/signals.c srcs/utils/idt.c

# Fichiers objets
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)
OBJECTS = $(ASM_OBJECTS) $(C_OBJECTS)

# Binaire final
KERNEL = kernel.bin

# Cible par défaut
all: $(KERNEL)

# Compilation assembleur
%.o: %.s
	$(ASM) $(ASM_FLAGS) $< -o $@

# Compilation C
%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

# Linkage
$(KERNEL): $(OBJECTS)
	$(LD) $(LD_FLAGS) $^ -o $@

# Génération de l'ISO
iso: $(KERNEL)
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "kfs1" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/$(KERNEL)' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o kfs1.iso iso/

# Nettoyage
clean:
	rm -f $(OBJECTS) $(KERNEL)
	rm -rf iso/
	rm -f kfs1.iso

# Nettoyage complet
fclean: clean
	rm -f kfs1.iso

# Test avec QEMU
run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

# Test avec ISO
runiso: iso
	qemu-system-i386 -cdrom kfs1.iso

# Rebuild complet
re: fclean all

.PHONY: all clean fclean re run runiso iso