/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:12:32 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 20:12:32 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "struct.h"

//ray.c
void	ray_init(t_ray *ray, double rayAngle);
void	draw_ray(t_god *god);
void	draw_line(t_god *god, double dx, double dy);
void	draw_one_ray(t_god *god, double angle, int i);
double	normalize_angle(double angle);
double	distance_between_points(double x1, double y1, double x2, double y2);
void	cal_distance(t_god *god, t_dpable_ray *horz_or_vert);
void	cal_ray(t_god *god, t_dpable_ray *horz_or_vert, int x_adjust, int y_adjust);
void	cal_horz_ray(t_god *god, t_dpable_ray *horz);
void	cal_vert_ray(t_god *god, t_dpable_ray *vert);

#endif