/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:16:23 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 21:16:24 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_info(t_god *god, t_3d_info *info)
{
	info->correct_distance = god->ray.distance \
		* cos(god->ray.ray_angle - god->player.rotationAngle);
	info->distance_project_plane = \
		(god->map.window_width / 2) / tan(FOV_ANGLE / 2);
	info->projected_wall_height = \
		(TILE_SIZE / info->correct_distance) * info->distance_project_plane;
	info->wallStripHeight = (int)info->projected_wall_height;
	info->wall_top = (god->map.window_height / 2) - (info->wallStripHeight / 2);
	info->correct_wall_top = info->wall_top;
	if (info->wall_top < 0)
		info->correct_wall_top = 0;
	info->wall_bottom = (god->map.window_height / 2) \
		+ (info->wallStripHeight / 2);
	info->correct_wall_bottom = info->wall_bottom;
	if (info->wall_top > god->map.window_height)
		info->correct_wall_bottom = god->map.window_height - 1;
	check_wall_direction(god, info);
}

void	check_wall_direction(t_god *god, t_3d_info *info)
{
	if (god->ray.wasHit_vertical == TRUE && \
		(god->player.x - god->ray.wall_hitX) > 0)
		info->direction = WE;
	else if (god->ray.wasHit_vertical == TRUE)
		info->direction = EA;
	else if ((god->player.y - god->ray.wall_hitY) > 0)
		info->direction = NO;
	else
		info->direction = SO;
}

int	select_color(t_god *god, t_3d_info *info, int idx)
{
	int	r;
	int	c;

	if (info->direction == WE || info->direction == EA)
		c = ((int)god->ray.wall_hitY % TILE_SIZE);
	else
		c = ((int)god->ray.wall_hitX % TILE_SIZE);
	c *= god->texture[info->direction].width / TILE_SIZE;
	r = (idx) * god->texture[info->direction].height / info->wallStripHeight;
	return (god->texture[info->direction].img.data \
		[r * god->texture[info->direction].width + c]);
}

void	render_3d_project_walls(t_god *god, int ray_num)
{
	t_3d_info	info;
	int			x;
	int			y;

	if (god->ray.distance == 0)
		god->ray.distance = 0.01;
	init_info(god, &info);
	y = info.correct_wall_top;
	while (y < info.correct_wall_bottom)
	{
		x = 0;
		while (x < WALL_STRIP_WIDTH)
		{
			if (god->img.data[god->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				god->img.data[god->map.window_width * y + (x + ray_num * \
					WALL_STRIP_WIDTH)] = select_color(god, &info, \
						(y - info.wall_top) * WALL_STRIP_WIDTH + x);
			x++;
		}
		y++;
	}
	draw_floor(god, ray_num, info.correct_wall_bottom);
	draw_sky(god, ray_num, info.correct_wall_top);
}