/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:01:12 by soylee            #+#    #+#             */
/*   Updated: 2023/03/12 15:01:13 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	print_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (1);
}

void	exit_error(char *msg)
{
	print_error(msg);
	exit(1);
}

int	check_extension(char *filename)
{
	size_t	idx;

	idx = ft_strlen(filename) - 4;
	if (ft_strncmp(filename + idx, ".cub", 4) == 0)
		return (TRUE);
	return (FALSE);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}
