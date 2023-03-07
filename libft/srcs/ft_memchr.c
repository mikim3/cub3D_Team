/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:09:24 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 03:09:48 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;
	unsigned char	value;

	i = 0;
	mem = (unsigned char *)s;
	value = (unsigned char)c;
	while (i < n)
	{
		if (*(mem + i) == value)
			return ((void *)(mem + i));
		i++;
	}
	return (0);
}
