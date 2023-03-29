/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:22:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/12 16:22:40 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_valid_char(t_god *god, char **str)
{
	int		i;
	int		tag;

	tag = 0;
	i = 0;
	while (str[i])
	{
		check_valid_line(god, str[i], i, &tag);
		i++;
	}
	if (!tag)
		exit_error("There is no Start Point");
}

void	check_valid_line(t_god *god, char *line, int i, int	*tag)
{
	int		j;
	char	tmp;

	j = 0;
	while (line[j])
	{
		tmp = line[j];
		if (tmp == ' ' || tmp == '0' || tmp == '1')
			;
		else if (tmp == 'N' || tmp == 'E' || tmp == 'W' || tmp == 'S')
		{
			if (*tag == 1)
				exit_error("Need 1 Start Point!");
			player_init(&god->player, j, i, tmp);
			*tag = 1;
		}
		else
			exit_error("Invalid Character in Map");
		j++;
	}
}

void	check_around_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_rows)
	{
		j = 0;
		while (j < map->map_cols)
		{
			if (map->map_matrix[i][j] == 0)
				check_space_pos(map, i, j);
			j++;
		}
		i++;
	}
}

void	check_space_pos(t_map *map, int r, int c)
{
	if (r == 0 || r == map->map_rows - 1 || c == 0 || c == map->map_cols - 1)
		exit_error("wall error");
	if (map->map_matrix[r - 1][c] == -1 || map->map_matrix[r + 1][c] == -1)
		exit_error("wall error");
	if (map->map_matrix[r][c - 1] == -1 || map->map_matrix[r][c + 1] == -1)
		exit_error("wall error");
}
