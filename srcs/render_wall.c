/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:16:23 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 15:11:41 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_info(t_cub *cub, t_3d_info *info)
{
	info->correct_distance = cub->ray.distance \
		* cos(cub->ray.ray_angle - cub->player.rotation_angle);
	info->distance_project_plane = \
		(cub->map.window_width / 2) / tan(FOV_ANGLE / 2);
	info->projected_wall_height = \
		(TILE_SIZE / info->correct_distance) * info->distance_project_plane;
	info->wall_strip_height = (int)info->projected_wall_height;
	info->wall_top = (cub->map.window_height / 2) - (info->wall_strip_height / 2);
	info->correct_wall_top = info->wall_top;
	info->wall_bottom = (cub->map.window_height / 2) \
		+ (info->wall_strip_height / 2);
	info->correct_wall_bottom = info->wall_bottom;
	if (info->wall_strip_height >= cub->map.window_height)
	{
		info->correct_wall_top = 0;
		info->correct_wall_bottom = cub->map.window_height - 1;
	}
	check_wall_direction(cub, info);
}

void	check_wall_direction(t_cub *cub, t_3d_info *info)
{
	if (cub->ray.washit_vertical == TRUE && \
		(cub->player.x - cub->ray.wall_hitx) > 0)
		info->direction = WE;
	else if (cub->ray.washit_vertical == TRUE)
		info->direction = EA;
	else if ((cub->player.y - cub->ray.wall_hity) > 0)
		info->direction = NO;
	else
		info->direction = SO;
}

int	select_color(t_cub *cub, t_3d_info *info, int idx)
{
	int	r;
	int	c;

	if (info->direction == WE || info->direction == EA)
		c = (int)cub->ray.wall_hity;
	else
		c = (int)cub->ray.wall_hitx;
	c = (c % TILE_SIZE) * cub->texture[info->direction].width / TILE_SIZE;
	r = (idx) * cub->texture[info->direction].height / info->wall_strip_height;
	return (cub->texture[info->direction].img.data \
		[r * cub->texture[info->direction].width + c]);
}

// (x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA
// EXC_BAD_ACCESS (code=1, address=0x129ecc614)  y 값이 갑자기 176532가 나옴
void	render_3d_project_walls(t_cub *cub, int ray_num)
{
	t_3d_info	info;
	int			x;
	int			y;

	if (cub->ray.distance == 0)
		cub->ray.distance = 0.01;
	init_info(cub, &info);
	y = info.correct_wall_top;
	while (y < info.correct_wall_bottom)
	{
		x = 0;
		while (x < WALL_STRIP_WIDTH)
		{
			if (cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				cub->img.data[cub->map.window_width * y + (x + ray_num * \
					WALL_STRIP_WIDTH)] = select_color(cub, &info, \
						(y - info.wall_top) * WALL_STRIP_WIDTH + x);
			x++;
		}
		y++;
	}
	draw_floor(cub, ray_num, info.correct_wall_bottom);
	draw_sky(cub, ray_num, info.correct_wall_top);
}
