/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:31:21 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 18:16:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_libc.h"

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

void	ft_f1()
{
	swap_screen();
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

void keyboard_handler()
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
		else if (character != '\0' && pressed == 0)
		{
			pressed = 1;
			ft_printf("%c", character);
		}
	}
}
