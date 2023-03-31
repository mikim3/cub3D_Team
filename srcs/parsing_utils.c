/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:26:31 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_map_info(t_map *map, char **str_map)
{
	int	i;
	int	max;
	int	len;
	int	tag;

	i = -1;
	max = -1;
	tag = 0;
	while (str_map[++i])
	{
		len = ft_strlen(str_map[i]);
		tag += 1;
		if (!is_emptyline(str_map[i]))
			tag = 0;
		if (max < len)
			max = len;
	}
	map->map_cols = max;
	map->map_rows = i - tag;
	map->window_width = map->map_cols * TILE_SIZE;
	map->window_height = map->map_rows * TILE_SIZE;
	map->ray_count = map->window_width;
}

int	get_color(char **str_num)
{
	int	color;
	int	num;
	int	i;

	i = 0;
	color = 0;
	while (i < 3)
	{
		if (!str_num[i])
			exit_error("lack of color");
		color <<= 8;
		num = ft_atoi(str_num[i]);
		if (!ft_isdigit_str(str_num[i]) || \
			(num == 0 && ft_strncmp(str_num[i], "0", 1)))
			exit_error("non-digit");
		if (num < 0 || num > 255)
			exit_error("color: Out of Range!");
		color |= num;
		i++;
	}
	return (color);
}

void	fill_map(t_cub *cub, char *line_map, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line_map);
	while (j < cub->map.map_cols)
	{
		if (j >= len || line_map[j] == ' ')
			cub->map.map_matrix[i][j] = -1;
		else if (line_map[j] == '1')
			cub->map.map_matrix[i][j] = 1;
		j++;
	}
}
