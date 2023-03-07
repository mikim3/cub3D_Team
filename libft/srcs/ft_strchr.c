/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 01:34:16 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 09:01:46 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	i = 0;
	cc = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
