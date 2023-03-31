/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:37:55 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 16:42:26 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cal_ray(t_cub *cub, t_dpable_ray *horz_or_vert, \
			int x_adjust, int y_adjust)
{
	double	next_touch_x;
	double	next_touch_y;

	next_touch_x = horz_or_vert->xintercept;
	next_touch_y = horz_or_vert->yintercept;
	while (next_touch_x >= 0 && next_touch_x <= cub->map.window_width && \
		next_touch_y >= 0 && next_touch_y <= cub->map.window_height)
	{
		if (is_wall(&(cub->map), next_touch_x \
			+ x_adjust, next_touch_y + y_adjust))
		{
			horz_or_vert->found_wallhit = TRUE;
			horz_or_vert->wall_hitx = next_touch_x;
			horz_or_vert->wall_hity = next_touch_y;
			break ;
		}
		else
		{
			next_touch_x += horz_or_vert->xstep;
			next_touch_y += horz_or_vert->ystep;
		}
	}
	cal_distance(cub, horz_or_vert);
}

void	cal_horz_ray(t_cub *cub, t_dpable_ray *horz)
{
	horz->found_wallhit = FALSE;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(cub->player.y / TILE_SIZE) * TILE_SIZE;
	horz->yintercept += three_operator(cub->ray.isray_facingdown, TILE_SIZE, 0);
	horz->xintercept = cub->player.x + (horz->yintercept \
		- cub->player.y) / tan(cub->ray.ray_angle);
	horz->ystep = TILE_SIZE;
	horz->ystep *= three_operator(cub->ray.isray_facingup, -1, 1);
	horz->xstep = TILE_SIZE / tan(cub->ray.ray_angle);
	horz->xstep *= three_operator(cub->ray.isray_facingleft \
		&& horz->xstep > 0, -1, 1);
	horz->xstep *= three_operator(cub->ray.isray_facingright \
		&& horz->xstep < 0, -1, 1);
	cal_ray(cub, horz, 0, three_operator(cub->ray.isray_facingup, -1, 0));
}

void	cal_vert_ray(t_cub *cub, t_dpable_ray *vert)
{
	vert->found_wallhit = FALSE;
	vert->wall_hitx = 0;
	vert->wall_hity = 0;
	vert->xintercept = floor(cub->player.x / TILE_SIZE) * TILE_SIZE;
	vert->xintercept += three_operator(cub->ray.isray_facingright, \
		TILE_SIZE, 0);
	vert->yintercept = cub->player.y + \
		(vert->xintercept - cub->player.x) * tan(cub->ray.ray_angle);
	vert->xstep = TILE_SIZE;
	vert->xstep *= three_operator(cub->ray.isray_facingleft, -1, 1);
	vert->ystep = TILE_SIZE * tan(cub->ray.ray_angle);
	vert->ystep *= three_operator((cub->ray.isray_facingup && \
		vert->ystep > 0), -1, 1);
	vert->ystep *= three_operator((cub->ray.isray_facingdown && \
		vert->ystep < 0), -1, 1);
	cal_ray(cub, vert, three_operator(cub->ray.isray_facingleft, -1, 0), 0);
}
