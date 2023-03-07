/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:27:17 by soylee            #+#    #+#             */
/*   Updated: 2022/04/16 03:13:58 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define INT_MIN -2147483648

static size_t	numlen(int n)
{
	size_t	cnt;

	cnt = 0;
	if (n == INT_MIN)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		cnt++;
	}
	while (n)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

static void	assign_num(char *s_num, int n, size_t len)
{
	int	i;

	if (n == INT_MIN)
	{
		ft_strlcpy(s_num, "-2147483648", 12);
		return ;
	}
	if (n == 0)
	{
		ft_strlcpy(s_num, "0", 2);
		return ;
	}
	if (n < 0)
	{
		s_num[0] = '-';
		n *= -1;
	}
	s_num[len] = 0;
	i = len - 1;
	while (n > 0)
	{
		s_num[i--] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*s_num;
	size_t	len;

	len = numlen(n);
	s_num = (char *)malloc((len + 1) * sizeof(char));
	if (s_num == 0)
		return (0);
	assign_num(s_num, n, len);
	return (s_num);
}
