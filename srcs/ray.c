/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:12:28 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 15:39:06 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_init(t_ray *ray, double rayAngle)
{
	ray->ray_angle = normalize_angle(rayAngle);
	ray->wall_hitx = 0;
	ray->wall_hity = 0;
	ray->distance = 0;
	ray->washit_vertical = FALSE;
	ray->isray_facingdown = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->isray_facingup = !ray->isray_facingdown;
	ray->isray_facingright = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI;
	ray->isray_facingleft = !ray->isray_facingright;
}

void	draw_ray(t_cub *cub)
{
	double	angle;
	int		i;

	i = 0;
	angle = cub->player.rotation_angle - (RAY_RANGE / 2.0);
	while (i < cub->map.ray_count)
	{
		draw_one_ray(cub, angle, i);
		angle += RAY_RANGE / cub->map.ray_count;
		i++;
	}
}

void	draw_line(t_cub *cub, double dx, double dy)
{
	double	ray_x;
	double	ray_y;
	int		x;
	int		y;
	double	max_value;

	ray_x = cub->player.x;
	ray_y = cub->player.y;
	max_value = fmax(fabs(dx), fabs(dy));
	if (max_value == 0)
		return ;
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(&(cub->map), ray_x, ray_y))
		{
			setting_map_location(&(cub->map), &x, &y, ray_x, ray_y);
			cub->img.data[cub->map.window_width * y + x] = RAY_COLOR;
		}
		else
			break ;
		ray_x += dx;
		ray_y += dy;
	}
}

void	draw_one_ray(t_cub *cub, double angle, int i)
{
	t_dpable_ray	horz;
	t_dpable_ray	vert;

	ray_init(&cub->ray, angle);
	cal_horz_ray(cub, &horz);
	cal_vert_ray(cub, &vert);
	if (vert.distance < horz.distance)
	{
		cub->ray.wall_hitx = vert.wall_hitx;
		cub->ray.wall_hity = vert.wall_hity;
		cub->ray.distance = vert.distance;
		cub->ray.washit_vertical = TRUE;
	}
	else
	{
		cub->ray.wall_hitx = horz.wall_hitx;
		cub->ray.wall_hity = horz.wall_hity;
		cub->ray.distance = horz.distance;
		cub->ray.washit_vertical = FALSE;
	}
	draw_line(cub, cub->ray.wall_hitx - cub->player.x,\
	cub->ray.wall_hity - cub->player.y);
	render_3d_project_walls(cub, i);
}
