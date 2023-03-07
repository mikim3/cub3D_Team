/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:39:59 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 02:56:44 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	size_t			len;
	char			*new;

	len = ft_strlen(s);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == 0)
		return (0);
	index = 0;
	while (index < len)
	{
		new[index] = f(index, s[index]);
		index++;
	}
	new[index] = 0;
	return (new);
}
