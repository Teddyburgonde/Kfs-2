/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:14:46 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 18:10:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMINAL_H
# define FT_TERMINAL_H

#include <ft_stdint.h>

typedef enum s_vga_color
{
	VGA_COLOR_BLACK = 0, // FG & BG
	VGA_COLOR_BLUE = 1, // FG & BG
	VGA_COLOR_GREEN = 2, // FG & BG
	VGA_COLOR_CYAN = 3, // FG & BG
	VGA_COLOR_RED = 4, // FG & BG
	VGA_COLOR_MAGENTA = 5, // FG & BG
	VGA_COLOR_BROWN = 6, // FG & BG
	VGA_COLOR_LIGHT_GREY = 7, // FG & BG
	VGA_COLOR_DARK_GREY = 8, // FG
	VGA_COLOR_LIGHT_BLUE = 9, // FG
	VGA_COLOR_LIGHT_GREEN = 10, // FG
	VGA_COLOR_LIGHT_CYAN = 11, // FG
	VGA_COLOR_LIGHT_RED = 12, // FG
	VGA_COLOR_LIGHT_MAGENTA = 13, // FG
	VGA_COLOR_LIGHT_BROWN = 14, // FG
	VGA_COLOR_WHITE = 15, // FG
}	vga_color;

uint8_t		vga_entry_color(vga_color fg, vga_color bg);
uint16_t	vga_entry(unsigned char uc, uint8_t color);

int	terminal_putstr(const char* data);
int	terminal_write(const char* data, size_t size);
int	terminal_putchar(char c);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	terminal_setcolor(uint8_t color);

void	terminal_clear(uint16_t *screen);
void	terminal_initialize(void);

void update_cursor(int x, int y);

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_MEMORY	0xB8000

#endif
