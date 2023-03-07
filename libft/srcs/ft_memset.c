/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:10:56 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 03:10:57 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buf;
	unsigned char	value;

	buf = (unsigned char *)b;
	value = (unsigned char)c;
	while (len-- > 0)
	{
		*(buf + len) = value;
	}
	return (b);
}
