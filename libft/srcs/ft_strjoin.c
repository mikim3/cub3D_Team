/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 01:14:29 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 09:04:01 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*new;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	new = (char *)malloc((len_1 + len_2 + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_strlcpy(new, s1, len_1 + 1);
	ft_strlcat(new, s2, len_1 + len_2 + 1);
	return (new);
}
