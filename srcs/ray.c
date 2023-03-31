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
	ray->isray_facingdown = ((ray->ray_angle > 0) && (ray->ray_angle < M_PI));
	ray->isray_facingup = !ray->isray_facingdown;
	ray->isray_facingright = ((ray->ray_angle < 0.5 * M_PI) \
		|| (ray->ray_angle > 1.5 * M_PI));
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
	t_d_point	ray;
	t_point		ray_i;
	t_point		p;
	double		max_value;

	ray.x = cub->player.x;
	ray.y = cub->player.y;
	max_value = fmax(fabs(dx), fabs(dy));
	if (max_value == 0)
		return ;
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		ray_i.x = ray.x;
		ray_i.y = ray.y;
		if (is_wall(&(cub->map), ray.x, ray.y))
			break ;
		setting_map_location(&(cub->map), &p.x, &p.y, ray_i);
		cub->img.data[cub->map.window_width * p.y + p.x] = RAY_COLOR;
		ray.x += dx;
		ray.y += dy;
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
	draw_line(cub, cub->ray.wall_hitx - cub->player.x, \
	cub->ray.wall_hity - cub->player.y);
	render_3d_project_walls(cub, i);
}
