/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:23:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 15:35:28 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	setting_map_location(t_map *map, int *x, int *y, t_point p2)
{
	if (MAP_LOCATION == LEFTUP_MAP)
	{
		*x = (int)(MINIMAP_SCALE * p2.x);
		*y = (int)(MINIMAP_SCALE * p2.y);
	}
	else if (MAP_LOCATION == LEFTDOWN_MAP)
	{
		*x = (int)(MINIMAP_SCALE * p2.x);
		*y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE \
			* map->map_rows + MINIMAP_SCALE * p2.y);
	}
	else if (MAP_LOCATION == RIGHTUP_MAP)
	{
		*x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE \
			* map->map_cols + MINIMAP_SCALE * p2.x);
		*y = (int)(MINIMAP_SCALE * p2.y);
	}
	else if (MAP_LOCATION == RIGHTDOWN_MAP)
	{
		*x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * \
			map->map_cols + MINIMAP_SCALE * p2.x);
		*y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * \
			map->map_rows + MINIMAP_SCALE * p2.y);
	}
}

void	fill_squares(t_img *img, t_map *map, t_point p, int color)
{
	int	i;
	int	j;

	setting_map_location(map, &p.x, &p.y, p);
	j = 0;
	while (j < (int)(MINIMAP_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINIMAP_SCALE * TILE_SIZE))
		{
			img->data[(int)(map->window_width) * (p.y + j) + (p.x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_2d_map(t_cub *cub)
{
	int		col;
	int		row;
	t_point	p;

	row = 0;
	while (row < cub->map.map_rows)
	{
		col = 0;
		while (col < cub->map.map_cols)
		{
			p.x = TILE_SIZE * col;
			p.y = TILE_SIZE * row;
			if (cub->map.map_matrix[row][col] == 1)
				fill_squares(&cub->img, &cub->map, p, TILE_2D_COLOR);
			else if (cub->map.map_matrix[row][col] == 0)
				fill_squares(&cub->img, &cub->map, p, WALL_2D_COLOR);
			col++;
		}
		row++;
	}
}

int	is_wall(t_map *map, double x, double y)
{
	int	idx_x;
	int	idx_y;

	if (x < 1 || x > map->window_width - 1 \
		|| y < 1 || y > map->window_height - 1)
	{
		return (1);
	}
	idx_x = x;
	idx_y = y;
	if (map->map_matrix[idx_y / TILE_SIZE][idx_x / TILE_SIZE] == 1)
		return (TRUE);
	if (map->map_matrix[(idx_y + 1) / TILE_SIZE][(idx_x + 1) / TILE_SIZE] == 1 \
	&& map->map_matrix[(idx_y - 1) / TILE_SIZE][(idx_x - 1) / TILE_SIZE] == 1)
		return (TRUE);
	if (map->map_matrix[(idx_y - 1) / TILE_SIZE][(idx_x + 1) / TILE_SIZE] == 1 \
	&& map->map_matrix[(idx_y + 1) / TILE_SIZE][(idx_x - 1) / TILE_SIZE] == 1)
		return (TRUE);
	return (FALSE);
}

int	check_edge(t_cub *cub, double x1, double y1, t_d_point new_p)
{
	t_point	p1;
	t_point	p2;

	p1.x = (int)(x1 / TILE_SIZE) - (int)(y1 / TILE_SIZE);
	p1.y = (int)(new_p.x / TILE_SIZE) - (int)(new_p.y / TILE_SIZE);
	p2.x = (int)(x1 / TILE_SIZE);
	p2.y = (int)(new_p.x / TILE_SIZE);
	if (p1.x == 1 && p1.y == 1)
		return (!ft_strchr("0NSEW", cub->map.map_matrix[p2.y - p1.y][p2.x]) \
			&& !ft_strchr("0NSEW", cub->map.map_matrix[p2.y][p2.x - p1.x]));
	if (p1.x == 1 && p1.y == -1)
		return (!ft_strchr("0NSEW", cub->map.map_matrix[p2.y - p1.y][p2.x]) \
			&& !ft_strchr("0NSEW", cub->map.map_matrix[p2.y][p2.x - p1.x]));
	if (p1.x == -1 && p1.y == 1)
		return (!ft_strchr("0NSEW", cub->map.map_matrix[p2.y - p1.y][p2.x]) \
			&& !ft_strchr("0NSEW", cub->map.map_matrix[p2.y][p2.x - p1.x]));
	if (p1.x == -1 && p1.y == -1)
		return (!ft_strchr("0NSEW", cub->map.map_matrix[p2.y - p1.y][p2.x]) \
			&& !ft_strchr("0NSEW", cub->map.map_matrix[p2.y][p2.x - p1.x]));
	return (FALSE);
}
