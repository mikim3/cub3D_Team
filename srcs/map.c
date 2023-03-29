/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:23:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 19:03:45 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 헤더에 define MAP_LOCATION 값에 따라
// 미니맵을 define 된거에 맞게 설정해주는 함수
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
void	render_map(t_god *god)
{
	int col;
	int row;

	row = 0;
	while (row < god->map.map_rows)
	{
		col = 0;
		while (col < god->map.map_cols)
		{
			if (god->map.map_matrix[row][col] == 1)
				fill_squares(&god->img, &god->map, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), TILE_2D_COLOR);
			else if (god->map.map_matrix[row][col] == 0)
				fill_squares(&god->img, &god->map, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), WALL_2D_COLOR);
			col++;
		}
		row++;
	}
}

int	is_wall(t_map *map, double x, double y)
{
	int	idx_x;
	int	idx_y;

	if (x < 0 || x > map->window_width || y < 0 || y > map->window_height)
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
// int check_edge(t_god *god, double x1, double x2, double y1, double y2)
// {
//	 // int dx;
//	 // int dy;

//	 // dx = (int)(x1 / TILE_SIZE) - (int)(x2 / TILE_SIZE);
//	 // dy = (int)(y1 / TILE_SIZE) - (int)(y2 / TILE_SIZE);
//	 // int dx2 = (int)(x1 / TILE_SIZE);
//	 // int dy2 = (int)(y1 / TILE_SIZE);

// 	// // 다음 좌표를 어디로 갈지를 dx,dy로 구하고? 그 위치에 있는걸
// 	// // 0NSEW 즉 벽이 아니면
//	 // if (dx == 1 && dy == 1)
//	 //	 return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//	 // if (dx == 1 && dy == -1)
//	 //	 return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//	 // if (dx == -1 && dy == 1)
//	 //	 return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//	 // if (dx == -1 && dy == -1)
//	 //	 return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//	 // return FALSE;

// }

int draw_sky(t_god *god, int ray_num, int wall_top_pixel)
{
	// y가 벽의 탑보다 높으면 그린다.
	for (int y = 0; y < wall_top_pixel; y++)
		for (int x = 0; x < WALL_STRIP_WIDTH; x++)
			if (god->img.data[god->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				god->img.data[god->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] = god->map.sky_color;
	return (0);
}

int draw_floor(t_god *god, int ray_num, int wall_bottom_pixel)
{
	for (int y = wall_bottom_pixel; y < god->map.window_height; y++)
		for (int x = 0; x < WALL_STRIP_WIDTH; x++)
			if (god->img.data[god->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				god->img.data[god->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] = god->map.floor_color;
	return (0);
}
