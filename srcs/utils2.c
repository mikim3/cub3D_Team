/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:01:12 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 15:18:13 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	three_operator(int condition, int trueValue, int falseValue)
{
	int	result;

	if (condition)
	{
		result = trueValue;
	}
	else
	{
		result = falseValue;
	}
	return (result);
}
