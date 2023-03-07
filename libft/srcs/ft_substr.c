/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:17:58 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 09:42:50 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	max;
	char	*substring;

	s_len = ft_strlen(s);
	if (start >= s_len)
		max = 0;
	else if (start + len >= s_len)
		max = s_len - start;
	else
		max = len;
	substring = (char *)malloc((max + 1) * sizeof(char));
	if (!substring)
		return (0);
	ft_strlcpy(substring, s + start, max + 1);
	return (substring);
}
