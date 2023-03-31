/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:26:29 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 15:39:18 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw_sky(t_cub *cub, int ray_num, int wall_top_pixel)
{
	int	y;
	int	x;

	y = 0;
	while (y++ < wall_top_pixel)
	{
		x = 0;
		while (x++ < WALL_STRIP_WIDTH)
		{
			if (cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] = cub->map.sky_color;
		}
	}
	return (0);
}

int	draw_floor(t_cub *cub, int ray_num, int wall_bottom_pixel)
{
	int	y;
	int	x;

	y = wall_bottom_pixel;
	while (y++ < cub->map.window_height)
	{
		x = 0;
		while (x++ < WALL_STRIP_WIDTH)
		{
			if (cub->img.data[cub->map.window_width * y + \
			(x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				cub->img.data[cub->map.window_width * y + \
				(x + ray_num * WALL_STRIP_WIDTH)] = cub->map.floor_color;
		}
	}
	return (0);
}
