/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:23:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	setting_map_location(t_map *map, int *x, int *y, int x2, int y2)
{
	if (MAP_LOCATION == LEFTUP_MAP)
	{
		*x = (int)(MINIMAP_SCALE * x2);
		*y = (int)(MINIMAP_SCALE * y2);
	}
	else if (MAP_LOCATION == LEFTDOWN_MAP)
	{
		*x = (int)(MINIMAP_SCALE * x2);
		*y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * map->map_rows + MINIMAP_SCALE * y2);
	}
	else if (MAP_LOCATION == RIGHTUP_MAP)
	{
		*x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * map->map_cols + MINIMAP_SCALE * x2);
		*y = (int)(MINIMAP_SCALE * y2);
	}
	else if (MAP_LOCATION == RIGHTDOWN_MAP)
	{
		*x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * map->map_cols + MINIMAP_SCALE * x2);
		*y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * map->map_rows + MINIMAP_SCALE * y2);
	}
}

// 받은 좌표에 정의(define)된 사각형의 크기에 따라서 한칸을 그린다.
void fill_squares(t_img *img, t_map *map, int x, int y, int color)
{
	int i;
	int j;

	setting_map_location(map, &x, &y, x, y);
	j = 0;
	while (j < (int)(MINIMAP_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINIMAP_SCALE * TILE_SIZE))
		{
			img->data[(int)(map->window_width) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

// 2D맵그리기
void	render_map(t_cub *cub)
{
	int col;
	int row;

	row = 0;
	while (row < cub->map.map_rows)
	{
		col = 0;
		while (col < cub->map.map_cols)
		{
			if (cub->map.map_matrix[row][col] == 1)
				fill_squares(&cub->img, &cub->map, (int)(TILE_SIZE * col), (int)(TILE_SIZE * row), TILE_2D_COLOR);
			else if (cub->map.map_matrix[row][col] == 0)
				fill_squares(&cub->img, &cub->map, (int)(TILE_SIZE * col), (int)(TILE_SIZE * row), WALL_2D_COLOR);
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

// (14)
// 꼭짓점
// 1 0
// 0 1
// 플레이어가 작고 이렇게 있을때 벽통과 버그를 막기위한 코드
// x1,y1은 플레이어 원래 위치   x2,y2는 플레이어 옮긴위치
int check_edge(t_cub *cub, double x1, double x2, double y1, double y2)
{
	int dx;
	int dy;
	int dx2;
	int dy2;
	
	dx = (int)(x1 / TILE_SIZE) - (int)(x2 / TILE_SIZE);
	dy = (int)(y1 / TILE_SIZE) - (int)(y2 / TILE_SIZE);
	dx2 = (int)(x1 / TILE_SIZE);
	dy2 = (int)(y1 / TILE_SIZE);
	// 다음 좌표를 어디로 갈지를 dx,dy로 구하고? 그 위치에 있는걸
	// 0NSEW 즉 벽이 아니면
	if (dx == 1 && dy == 1)
		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
	if (dx == 1 && dy == -1)
		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
	if (dx == -1 && dy == 1)
		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
	if (dx == -1 && dy == -1)
		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
	return (FALSE);
}

int draw_sky(t_cub *cub, int ray_num, int wall_top_pixel)
{
	// y가 벽의 탑보다 높으면 그린다.
	for (int y = 0; y < wall_top_pixel; y++)
		for (int x = 0; x < WALL_STRIP_WIDTH; x++)
			if (cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] = cub->map.sky_color;
	return (0);
}

int draw_floor(t_cub *cub, int ray_num, int wall_bottom_pixel)
{
	for (int y = wall_bottom_pixel; y < cub->map.window_height; y++)
		for (int x = 0; x < WALL_STRIP_WIDTH; x++)
			if (cub->img.data[cub->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				cub->img.data[cub->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] = cub->map.floor_color;
	return (0);
}
