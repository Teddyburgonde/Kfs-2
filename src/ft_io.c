/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:50:44 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 12:05:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

uint8_t	inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile ( "inb %w1, %b0"
				: "=a"(ret)
				: "Nd"(port)
				: "memory");
	return ret;
}

void	outb(uint16_t port, uint8_t val)
{
	__asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

# define NULL_STRING	"(null)"
# define NIL_STR		"(nil)"
# define LOWER_HEX		"0123456789abcdef"
# define UPPER_HEX		"0123456789ABCDEF"

int	ft_putnbr(int n)
{
	if (n < 0)
		return (terminal_putchar('-') + ft_putnbr(n * -1));
	if (n >= 0 && n <= 9)
		return (terminal_putchar(n % 10 + '0'));
	return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}

int	ft_putnbr_hex(int n, char *set)
{
	if (n < 0)
		return (terminal_putchar('-') + ft_putnbr_hex(n * -1, set));
	if (n >= 0 && n <= 15)
		return (terminal_putchar(set[n % 16]));
	return (ft_putnbr_hex(n / 16, set) + ft_putnbr_hex(n % 16, set));
}

static int	ft_putnbr_hex_u(unsigned int n, char *set)
{
	if (n >= 0 && n <= 15)
		return (terminal_putchar(set[n % 16]));
	return (ft_putnbr_hex_u(n / 16, set) + ft_putnbr_hex_u(n % 16, set));
}

int	ft_putadress(unsigned int n)
{
	if (n == 0)
		return (terminal_putstr(NIL_STR));
	return (terminal_putstr("0x") + ft_putnbr_hex_u(n, LOWER_HEX));
}

static int	ft_exec_flag(va_list *args, char c)
{
	if (c == 'c')
		return (terminal_putchar((char)va_arg(*args, int)));
	if (c == 's')
		return (terminal_putstr(va_arg(*args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	if (c == 'u')
		return (ft_putnbr(va_arg(*args, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_hex(va_arg(*args, unsigned int), LOWER_HEX));
	if (c == 'X')
		return (ft_putnbr_hex(va_arg(*args, unsigned int), UPPER_HEX));
	if (c == 'p')
		return (ft_putadress(va_arg(*args, unsigned int)));
	if (c == '%')
		return (terminal_putchar('%'));
	return (terminal_putchar('%') + terminal_putchar(c));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		res;

	if (!str)
		return (-1);
	res = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			res += ft_exec_flag(&args, *(str + 1));
			str += 2;
			continue ;
		}
		res += terminal_putchar((char)*(str++));
	}
	va_end(args);
	return (res);
}
