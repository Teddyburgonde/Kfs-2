/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:49:54 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 15:08:54 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <ft_terminal.h>

typedef __builtin_va_list va_list;

#define va_start(ap, last)	__builtin_va_start(ap, last)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)
#define va_end(ap)			__builtin_va_end(ap)

int		ft_printf(const char *str, ...);

// From sys/io.h
uint8_t	inb(uint16_t port);
void	outb(uint16_t port, uint8_t val);
//

#endif
