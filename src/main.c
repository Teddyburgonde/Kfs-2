/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:03:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 18:14:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernel.h"
#include "ft_io.h"
#include "ft_keyboard.h"

# define KFS_VERSION "kfs-1"
# define KFS_CREDITS "(by tebandam & mbatty)"

# define KFS_HEADER "\
42      :::      ::::::::\n\
      :+:      :+:    :+:\n\
    +:+ +:+         +:+  \n\
  +#+  +:+       +#+     \n\
+#+#+#+#+#+   +#+        \n\
     #+#    #+#          \n\
    ###   ###########    \n\
\n\
Welcome to " KFS_VERSION "! " KFS_CREDITS "\n"

# define SHELL_PROMPT ":>"

void	print_header_and_colors()
{
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	ft_printf("%s", KFS_HEADER);

	// Prints all available foreground/background colors
	for (int fg = 0; fg <= VGA_COLOR_WHITE; fg++)
	{
		int	bg = fg <= VGA_COLOR_LIGHT_GREY ? fg : VGA_COLOR_BLACK;

		terminal_setcolor(vga_entry_color(fg, bg));
		ft_printf("#");
	}
	ft_printf("\n");
}

uint16_t	screen_2[VGA_WIDTH * VGA_HEIGHT];
int			cursor_x2 = 0;
int			cursor_y2 = 0;
int			cursor_x = 0;
int			cursor_y = 0;

void	main(void)
{
	terminal_initialize();
	terminal_clear(screen_2);

	print_header_and_colors();

	terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	ft_printf("%s", SHELL_PROMPT);
	while (1)
	{
		keyboard_handler();
	}
}
