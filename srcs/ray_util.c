/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:38:57 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 14:23:12 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	normalize_angle(double angle)
{
	if (angle >= 0)
	{
		while (angle >= M_PI * 2)
			angle -= M_PI * 2;
	}
	else
	{
		while (angle <= 0)
			angle += M_PI * 2;
	}
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cal_distance(t_cub *cub, t_dpable_ray *horz_or_vert)
{
	if (horz_or_vert->found_wallhit == TRUE)
		horz_or_vert->distance = distance_between_points(cub->player.x, \
			cub->player.y, horz_or_vert->wall_hitx, horz_or_vert->wall_hity);
	else
		horz_or_vert->distance = 999999999999;
}
