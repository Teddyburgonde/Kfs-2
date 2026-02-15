/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:31:21 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/15 12:44:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_libc.h"
#include "ft_keyboard.h"
#include "gdt.h"

unsigned char get_scancode()
{
	unsigned char scancode = 0;
	scancode = inb(0x60);
	return scancode;
}

extern uint16_t		*terminal_buffer;
extern uint16_t		screen_2[VGA_WIDTH * VGA_HEIGHT];
extern int			cursor_x2;
extern int			cursor_y2;
extern int			cursor_x;
extern int			cursor_y;


void	swap_screen()
{
	uint16_t	buf[VGA_WIDTH * VGA_HEIGHT];
	int			tmpx;
	int			tmpy;

	tmpx = cursor_x;
	tmpy = cursor_y;
	ft_memcpy(buf, terminal_buffer, (VGA_WIDTH * VGA_HEIGHT) * sizeof(uint16_t));

	cursor_x = cursor_x2;
	cursor_y = cursor_y2;
	ft_memcpy(terminal_buffer, screen_2, (VGA_WIDTH * VGA_HEIGHT) * sizeof(uint16_t));

	ft_memcpy(screen_2, buf, (VGA_WIDTH * VGA_HEIGHT) * sizeof(uint16_t));
	cursor_x2 = tmpx;
	cursor_y2 = tmpy;
	update_cursor(cursor_x, cursor_y);
}

void print_tux()
{
	/* Black for the body */
	terminal_setcolor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

	/* White for the background/belly */
	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	ft_printf("       _nnnn_\n");
	ft_printf("      dGGGGMMb\n");

	/* Yellow for eyes area */
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
	ft_printf("     @p~qp~~qMb\n");
	ft_printf("     M|");
	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	ft_printf("@||@");
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
	ft_printf(") M|\n");

	/* Yellow beak */
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
	ft_printf("     @,----.JM|\n");

	/* White belly */
	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	ft_printf("    JS^\\__/  qKL\n");
	ft_printf("   dZP        qKRb\n");
	ft_printf("  dZP          qKKb\n");
	ft_printf(" fZP            SMMb\n");
	ft_printf(" HZM            MMMM\n");
	ft_printf(" FqM            MMMM\n");

	/* Feet */
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
	ft_printf("__| \".        |\\dS\"qML\n");
	ft_printf("|    `.       | `' \\Zq\n");
	ft_printf("_)      \\.___.,|     .'\n");
	ft_printf("\\____   )MMMMMP|   .'\n");
	ft_printf("     `-'       `--'\n");

	/* Reset color */
	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}


static void	ft_f1()
{
	swap_screen();
}


static void ft_shutdown()
{
    outw(0x604, 0x2000); // Qemu shutdown
	outw(0x4004, 0x3400); // Virtualbox shutdown
}


int	pressed = 0;

char scancode_to_char[256] = {
	// Letter a-z
	[0x1E] = 'a',
	[0x30] = 'b',
	[0x2E] = 'c',
	[0x20] = 'd',
	[0x12] = 'e',
	[0x21] = 'f',
	[0x22] = 'g',
	[0x23] = 'h',
	[0x17] = 'i',
	[0x24] = 'j',
	[0x25] = 'k',
	[0x26] = 'l',
	[0x32] = 'm',
	[0x31] = 'n',
	[0x18] = 'o',
	[0x19] = 'p',
	[0x10] = 'q',
	[0x13] = 'r',
	[0x1F] = 's',
	[0x14] = 't',
	[0x16] = 'u',
	[0x2F] = 'v',
	[0x11] = 'w',
	[0x2D] = 'x',
	[0x15] = 'y',
	[0x2C] = 'z',

	// Digits 0-9
	[0x0B] = '0',
	[0x02] = '1',
	[0x03] = '2',
	[0x04] = '3',
	[0x05] = '4',
	[0x06] = '5',
	[0x07] = '6',
	[0x08] = '7',
	[0x09] = '8',
	[0x0A] = '9',

	[0x1C] = '\n',  // Enter
	[0x39] = ' ',   // Space
	[0x0E] = '\b', // Backspace
};

void	print_help()
{
	ft_printf("help, shutdown, tux, pstack\n");
}

void	ft_readline()
{
	char	shell_buf[1024] = {0};
	int		index = 0;

	while (1)
	{
		char	key = keyboard_handler();
		if (key != '\0')
		{
			if (key == '\n')
			{
				if (!ft_strncmp(sizeof("help"), "help", shell_buf))
					print_help();
				else if (!ft_strncmp(sizeof("shutdown"), "shutdown", shell_buf))
					ft_shutdown();
				else if (!ft_strncmp(sizeof("tux"), "tux", shell_buf))
					print_tux();
				else if (!ft_strncmp(sizeof("pstack"), "pstack", shell_buf))
					print_stack();
				ft_printf("CMD: '%s'\n%s", shell_buf, SHELL_PROMPT);
				ft_memset(shell_buf, 0, sizeof(shell_buf));
				index = 0;
			}
			else if (key == '\b' && index > 0)
				shell_buf[--index] = '\0';
			else if (index < 1023)
				shell_buf[index++] = key;
		}
	}
}

char	keyboard_handler()
{
	unsigned char scancode;
	scancode = get_scancode();

	if (scancode & 0x80) // Touche relâchée (bit 7 = 1)
	{
		pressed = 0;
	}
	else // Touche pressée
	{
		char character = '\0';
		character = scancode_to_char[scancode];

		if (scancode == 0x3B && pressed == 0)
		{
			ft_f1();
			pressed = 1;
		}
		else if (scancode == 0x3D && pressed == 0)
		{
    		ft_shutdown();
    		pressed = 1;
		}
		else if (character != '\0' && pressed == 0)
		{
			pressed = 1;
			ft_printf("%c", character);
			return (character);
		}
	}
	return ('\0');
}
