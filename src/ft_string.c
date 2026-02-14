/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:13:35 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/13 10:28:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlen(const char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strncmp(size_t n, const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] == s2[i]) && (s1[i] || s2[i]))
		i++;
	if (i < n)
		return ((uint8_t)s1[i] - (uint8_t)s2[i]);
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		*(uint8_t *)dest++ = *(uint8_t *)src++;
		n--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		while (i < n)
		{
			*(uint8_t *)(dest + i) = *(uint8_t *)(src + i);
			i++;
		}
	}
	else if (dest > src)
	{
		i = n - 1;
		while ((int)i >= 0)
		{
			*(uint8_t *)(dest + i) = *(uint8_t *)(src + i);
			i--;
		}
	}
	return (dest);
}
