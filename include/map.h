/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:34:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 21:34:28 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "struct.h"

//map.c
void	setting_map_location(t_map *map, int *x, int *y, int x2, int y2);
void	fill_squares(t_img *img, t_map *map, int x, int y, int color);
void	render_map(t_god *god);
int		is_wall(t_map *map, double x, double y);
int		draw_sky(t_god *god, int ray_num, int wall_top_pixel);
int		draw_floor(t_god *god, int ray_num, int wall_bottom_pixel);

#endif
