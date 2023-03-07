/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:42:10 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 02:11:40 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	srch_idx;

	if (*little == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	srch_idx = len - ft_strlen(little);
	i = 0;
	while (i <= srch_idx && big[i] != 0)
	{
		j = 0;
		while (big[i + j] == little[j])
		{
			j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
