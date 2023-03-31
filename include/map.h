/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:34:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 14:46:57 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "struct.h"

// minimap location
# define LEFTUP_MAP		1
# define LEFTDOWN_MAP	2
# define RIGHTUP_MAP	3
# define RIGHTDOWN_MAP	4

// map.c
void	setting_map_location(t_map *map, int *x, int *y, int x2, int y2);
void	fill_squares(t_img *img, t_map *map, int x, int y, int color);
void	render_map(t_cub *cub);
int		is_wall(t_map *map, double x, double y);
int		draw_sky(t_cub *cub, int ray_num, int wall_top_pixel);
int		draw_floor(t_cub *cub, int ray_num, int wall_bottom_pixel);

// int     check_edge(t_cub *cub, double x1, double x2, double y1, double y2);
int		check_edge(t_cub *cub, double x1, double x2, t_point new_point);

// int check_edge(t_cub *cub, double x1, double y1, double x2, double y2)
// {
// 	int	dx;
// 	int	dy;
// 	int	dx2;
// 	int	dy2;

// 	dx = (int)(x1 / TILE_SIZE) - (int)(y1 / TILE_SIZE);
// 	dy = (int)(x2 / TILE_SIZE) - (int)(y2 / TILE_SIZE);
// 	dx2 = (int)(x1 / TILE_SIZE);
// 	dy2 = (int)(x2 / TILE_SIZE);
// 	// 다음 좌표를 어디로 갈지를 dx,dy로 구하고? 그 위치에 있는걸
// 	// 0NSEW 즉 벽이 아니면
// 	if (dx == 1 && dy == 1)
// 		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
// 	if (dx == 1 && dy == -1)
// 		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
// 	if (dx == -1 && dy == 1)
// 		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
// 	if (dx == -1 && dy == -1)
// 		return (ft_strchr("0NSEW", cub->map.map_matrix[dy2 - dy][dx2]) == NULL) && (ft_strchr("0NSEW", cub->map.map_matrix[dy2][dx2 - dx]) == NULL);
// 	return (FALSE);
// }




#endif
