/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:35:36 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 10:34:21 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (c == set[i++])
			return (1);
	return (0);
}

static size_t	cnt_not_set(char const *s1, char const *set)
{
	size_t	len;
	size_t	cnt;
	size_t	i;

	len = ft_strlen(s1);
	cnt = len;
	i = 0;
	while (i < len && is_set(s1[i++], set))
		cnt--;
	if (cnt == 0)
		return (0);
	i = len;
	while (i > 0 && is_set(s1[--i], set))
		cnt--;
	return (cnt);
}

static void	cp_not_set(char *new, char const *s1, char const *set, size_t len)
{
	int		index;

	index = 0;
	while (is_set(s1[index], set))
		index++;
	ft_strlcpy(new, s1 + index, len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	len;

	len = cnt_not_set(s1, set);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (0);
	cp_not_set(new, s1, set, len);
	return (new);
}
