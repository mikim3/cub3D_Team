/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:34:16 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 09:53:28 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	cc;

	len = ft_strlen(s);
	cc = (char)c;
	while (1)
	{
		if (s[len] == cc)
			return ((char *)s + len);
		if (len == 0)
			return (0);
		len--;
	}
}
