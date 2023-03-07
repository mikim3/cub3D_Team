/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:55:56 by soylee            #+#    #+#             */
/*   Updated: 2022/04/30 10:37:58 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_word_num(char const *s, char c)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	if (*s == 0)
		return (0);
	if (s[i] != c)
		num++;
	while (s[i + 1] != 0)
	{
		if (s[i] == c && s[i + 1] != c)
			num++;
		i++;
	}
	return (num);
}

static size_t	cnt_word_len(char const *word, char c)
{
	int		i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (word[i] != 0 && word[i] != c)
	{
		cnt++;
		i++;
	}
	return (cnt);
}

static char	**allocate_word(char **split, char const *s, char c, size_t num)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < num)
	{
		while (*s == c)
			s++;
		len = cnt_word_len(s, c);
		split[i] = (char *)malloc((len + 1) * sizeof(char));
		if (split[i] == 0)
		{
			free(split);
			return (0);
		}
		ft_strlcpy(split[i], s, len + 1);
		s += len;
		i++;
	}
	split[i] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	num;
	char	**split;

	num = cnt_word_num(s, c);
	split = (char **)malloc((num + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	if (num == 0)
	{
		*split = 0;
		return (split);
	}
	if (!allocate_word(split, s, c, num))
		return (0);
	return (split);
}
