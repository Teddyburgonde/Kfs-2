NAME := kfs-2.iso
KERNEL := kernel

# Compilers
CC :=	gcc
ASM :=	nasm
#

# Flags
CFLAGS :=	-m32 -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs
ASMFLAGS :=	-f elf32
#

# Sources
C_SRCS :=	src/main.c\
			src/ft_string.c\
			src/ft_terminal.c\
			src/ft_io.c\
			src/ft_keyboard.c\
			src/gdt.c\

ASM_SRCS :=	src/boot.asm\

INCLUDES :=	inc/\
#

INCLUDES :=	$(addprefix -I, $(INCLUDES))

# Config
LINKER := cfg/linker.ld
GRUB_CFG := cfg/grub.cfg
#

BUILD_DIR := build

# Objects
OBJ_DIR :=	$(BUILD_DIR)/obj
C_OBJS :=	$(C_SRCS:%.c=$(OBJ_DIR)/%.o)
ASM_OBJS :=	$(ASM_SRCS:%.asm=$(OBJ_DIR)/%.o)
#

all: $(NAME)

$(NAME): $(C_OBJS) $(ASM_OBJS)
	@ld -m elf_i386 -T $(LINKER) -o $(BUILD_DIR)/$(KERNEL) $(C_OBJS) $(ASM_OBJS)
	@mkdir -p $(BUILD_DIR)/iso/boot/grub
	@cp $(BUILD_DIR)/$(KERNEL) $(BUILD_DIR)/iso/boot/
	@cp $(GRUB_CFG) $(BUILD_DIR)/iso/boot/grub/
	@grub-mkrescue -o kfs-2.iso $(BUILD_DIR)/iso/

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(ASM) $(ASMFLAGS) $< -o $@

re: fclean all

fclean: clean
	@echo Removed $(NAME)
	@rm -rf $(NAME)

clean:
	@echo Removed $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)

.PHONY: all clean fclean re
