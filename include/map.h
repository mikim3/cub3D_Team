/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:34:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/29 11:43:15 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "struct.h"

/* 맵위 위치 */
# define LEFTUP_MAP (1)
# define LEFTDOWN_MAP (2)
# define RIGHTUP_MAP (3)
# define RIGHTDOWN_MAP (4)

//map.c
void	setting_map_location(t_map *map, int *x, int *y, int x2, int y2);
void	fill_squares(t_img *img, t_map *map, int x, int y, int color);
void	render_map(t_god *god);
int		is_wall(t_map *map, double x, double y);
int		draw_sky(t_god *god, int ray_num, int wall_top_pixel);
int		draw_floor(t_god *god, int ray_num, int wall_bottom_pixel);
int     check_edge(t_god *god, double x1, double x2, double y1, double y2);

#endif
