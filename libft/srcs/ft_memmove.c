/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:10:02 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 03:10:40 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len == 0)
		return (dst);
	if (src < dst && src + len > dst)
	{
		while (len-- > 0)
		{
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
		}
	}
	else if (dst < src && dst + len > src)
	{
		i = 0;
		while (i < len)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
