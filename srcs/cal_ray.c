/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:37:55 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 14:26:36 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 실질적으로 벽의 위치를 찾는 함수
// x_adjust, y_adjust는 플레이어가 왼쪽이랑 위쪽 볼때 벽이 밀려서 나타나는 현상이 있이서 값을 보정해주었다.
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

// 양옆으로 쭉 그어진 행모양 기준선
// cal_ray함수에서 벽의위치를 찾는데 쓰일
// xintercept, yintercept, xstep, ystep의 값을 정해줌
void	cal_horz_ray(t_cub *cub, t_dpable_ray *horz)
{
	horz->found_wallhit = FALSE;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;

	horz->yintercept = floor(cub->player.y  / TILE_SIZE) * TILE_SIZE;
	horz->yintercept += cub->ray.isray_facingdown ? TILE_SIZE : 0;
	horz->xintercept = cub->player.x + (horz->yintercept \
		- cub->player.y) / tan(cub->ray.ray_angle);
	horz->ystep = TILE_SIZE;
	horz->ystep *= cub->ray.isray_facingup ? -1 : 1;
	horz->xstep = TILE_SIZE / tan(cub->ray.ray_angle);
	horz->xstep *= (cub->ray.isray_facingleft && horz->xstep > 0) ? -1 : 1;
	horz->xstep *= (cub->ray.isray_facingright && horz->xstep < 0) ? -1 : 1;
	cal_ray(cub, horz, 0, cub->ray.isray_facingup ? -1 : 0);
}

void cal_vert_ray(t_cub *cub, t_dpable_ray *vert)
{
	vert->found_wallhit = FALSE;
	vert->wall_hitx = 0;
	vert->wall_hity = 0;

	vert->xintercept = floor(cub->player.x  / TILE_SIZE) * TILE_SIZE;
	vert->xintercept += cub->ray.isray_facingright ? TILE_SIZE : 0;
	vert->yintercept = cub->player.y + (vert->xintercept - cub->player.x) * tan(cub->ray.ray_angle);
	vert->xstep = TILE_SIZE;
	vert->xstep *= cub->ray.isray_facingleft ? -1 : 1;
	vert->ystep = TILE_SIZE * tan(cub->ray.ray_angle);
	vert->ystep *= (cub->ray.isray_facingup && vert->ystep > 0) ? -1 : 1;
	vert->ystep *= (cub->ray.isray_facingdown && vert->ystep < 0) ? -1 : 1;

	cal_ray(cub, vert, cub->ray.isray_facingleft ? -1 : 0, 0);
}
