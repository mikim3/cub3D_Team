/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:23:58 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/01 21:55:49 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int mini_map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 헤더에 define MAP_LOCATION 값에 따라
// 미니맵을 define 된거에 맞게 설정해주는 함수
void    setting_map_location(int *x, int *y, int x2, int y2)
{
    if (MAP_LOCATION == LEFTUP_MAP)
    {
        *x = (int)(MINIMAP_SCALE * x2);
        *y = (int)(MINIMAP_SCALE * y2);
    }
    else if (MAP_LOCATION == LEFTDOWN_MAP)
    {
        *x = (int)(MINIMAP_SCALE * x2);
        *y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * MAP_NUM_ROWS + MINIMAP_SCALE * y2);
    }
    else if (MAP_LOCATION == RIGHTUP_MAP)
    {
        *x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * MAP_NUM_COLS + MINIMAP_SCALE * x2);
        *y = (int)(MINIMAP_SCALE * y2);
    }
    else if (MAP_LOCATION == RIGHTDOWN_MAP)
    {
        *x = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * MAP_NUM_COLS + MINIMAP_SCALE * x2);
        *y = (int)((1 - MINIMAP_SCALE) * TILE_SIZE * MAP_NUM_ROWS + MINIMAP_SCALE * y2);
    }
}


// 이전버전 (8)에서 바뀜 fill_squares()
// void fill_squares(t_img *img, int x, int y, int color)
// {
// 	int i;
// 	int j;

// 	j = 0;
// 	while (j < (int)(MINI_SCALE * TILE_SIZE))
// 	{
// 		i = 0;
// 		while (i < (int)(MINI_SCALE * TILE_SIZE))
// 		{
// 			img->data[(int)(MINI_SCALE * WINDOW_WIDTH) * (y + j) + (x + i)] = color;
// 			i++;
// 		}
// 		j++;
// 	}
// }

// 받은 좌표에 정의(define)된 사각형의 크기에 따라서 한칸을 그린다.
void fill_squares(t_img *img, int x, int y, int color)
{
	int i;
	int j;

	setting_map_location(&x, &y, x, y);
	j = 0;
	while (j < (int)(MINIMAP_SCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINIMAP_SCALE * TILE_SIZE))
		{
			img->data[(int)(WINDOW_WIDTH) * (y + j) + (x + i)] = color;
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
	while (row < MAP_NUM_ROWS)
	{
		col = 0;
		while (col < MAP_NUM_COLS)
		{
			if (mini_map[row][col] == 1)
				fill_squares(&god->img, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0x000000);
			else
				fill_squares(&god->img, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0xffffff);
			col++;
		}
		row++;
	}
}

int	is_wall(double x, double y)
{
	int xX;
	int yY;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
	{
		return (1);
	}
	// floor는 소수점 무시 그냥 int형 값으로 바꾸려고 넣음
	xX = floor(x / TILE_SIZE);
	yY = floor(y / TILE_SIZE);

	return mini_map[yY][xX] != 0;
}

// (14)
// 꼭짓점
// 1 0
// 0 1
// 플레이어가 작고 이렇게 있을때 벽통과 버그를 막기위한 코드
// int check_edge(t_god *god, double x1, double x2, double y1, double y2)
// {
//     // int dx;
//     // int dy;

//     // dx = (int)(x1 / TILE_SIZE) - (int)(x2 / TILE_SIZE);
//     // dy = (int)(y1 / TILE_SIZE) - (int)(y2 / TILE_SIZE);
//     // int dx2 = (int)(x1 / TILE_SIZE);
//     // int dy2 = (int)(y1 / TILE_SIZE);

// 	// // 다음 좌표를 어디로 갈지를 dx,dy로 구하고? 그 위치에 있는걸
// 	// // 0NSEW 즉 벽이 아니면
//     // if (dx == 1 && dy == 1)
//     //     return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//     // if (dx == 1 && dy == -1)
//     //     return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//     // if (dx == -1 && dy == 1)
//     //     return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//     // if (dx == -1 && dy == -1)
//     //     return (ft_strchr("0NSEW", god->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", god->map.map_matrix[dy2][dx2 - dx]) == NULL);
//     // return FALSE;

// }

int draw_sky(t_god *god, int ray_num, int wall_top_pixel, int color)
{
	// y가 벽의 탑보다 높으면 그린다.
    for (int y = 0; y < wall_top_pixel; y++)
        for (int x = 0; x < WALL_STRIP_WIDTH; x++)
            if (god->img.data[WINDOW_WIDTH * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_WALL)
                god->img.data[WINDOW_WIDTH * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] = color;
    return (0);
}

int draw_floor(t_god *god, int ray_num, int wall_bottom_pixel, int color)
{
    for (int y = wall_bottom_pixel; y < WINDOW_HEIGHT; y++)
        for (int x = 0; x < WALL_STRIP_WIDTH; x++)
            if (god->img.data[WINDOW_WIDTH * y + (x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_WALL)
                god->img.data[WINDOW_WIDTH * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
    return (0);
}


