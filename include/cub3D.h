/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:06 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 11:37:07 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H__
# define __CUB3D_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES //math.h안에 M_PI값을 쓸수 있게해주는 변수
#include <math.h> // floor,
#include <float.h> // DBL_MAX
#include "mlx.h"
#include "libft.h"

#include "struct.h"
#include "utils.h"
#include "parsing.h"

// 1배율은 꽉참
#define MINI_SCALE 1
#define TILE_SIZE 40
// 맵의 행 크기, 파싱을 받을 경우 그 맵의 크기를 구해서 만들어 줘야 된다.
// #define MAP_NUM_ROWS 12
// #define MAP_NUM_COLS 20
// #define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
// #define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

/* key event */
# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT			17

/* key */
# define KEY_ESC    53
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2

# define KEY_LEFT	(123)
# define KEY_RIGHT	(124)
# define KEY_UP 	(126)
# define KEY_DOWN	(125)

/* math */
# define FOV_ANGLE (60 * (M_PI / 180.0))

# define	RAY_RANGE (FOV_ANGLE) // 내가 보고 있다는걸 몇도로 나타낼까 시야각

/*    */
# define TRUE		(1)
# define FALSE		(0)

/* 맵위 위치 */
# define LEFTUP_MAP (1)
# define LEFTDOWN_MAP (2)
# define RIGHTUP_MAP (3)
# define RIGHTDOWN_MAP (4)

// 괄호() 안에 값으로 맵의 위치를 설정
# define MINIMAP_SCALE (0.25)
# define MAP_LOCATION (RIGHTDOWN_MAP)
# define PLAYER_THICKNESS 6
# define WALKSPEED			(1)
# define TURNSPEED			(1.5 * (M_PI / 180))
# define WALL_STRIP_WIDTH	(1)
# define IS_3D_AREA			(0x663333)
# define VIRTICAL_COLOR		(0x00FF00)
# define HORIZON_COLOR		(0x0000FF)
# define PLAYER_2D_COLOR	(0x00AAAA)
# define SKY_COLOR			(0x444444)
# define FLOOR_COLOR		(0x000000)
# define RAY_COLOR			(0xFF0000)
# define VERT_WALL_COLOR	(0xFFFFFF)
# define HORI_WALL_COLOR	(0xAAAAAA)
// # define RAY_RANGE			(FOV_ANGLE)

# define UPDOWNSPEED		(3)

void	fill_squares(t_img *img, t_map *map, int x, int y, int color);

/* render */
void	render_master(t_god *god); //모든 렌더링을 수행해주는 함수
void	render_map(t_god	*god);
// void	render_map(t_mlx *mlx, t_img *map);
// void	render_player(t_mlx *mlx, t_img *map);
void	render_player(t_god *god);
void	render_3D_project_walls(t_god *god, int ray_num);



void    setting_map_location(t_map *map, int *x, int *y, int x2, int y2);

/* player */
// void player_init(t_player *player, t_map *map);
void player_init(t_player *player, double x, double y, char direction);
// int    draw_player(t_mlx *mlx, t_player *player, t_img *map);
// int    draw_player(t_god *god);
int    draw_player(t_god *god, t_player *player, t_img *img);
int		update_player(t_god *god);

void		key_init(t_key *key);
int        key_press(int keycode, t_key *key);
int        key_release(int keycode, t_key *key);
int		key_exit(void);

int		is_wall(t_map *map, double x, double y);
// int		check_edge(t_god *god, double x1, double x2, double y1, double y2);

/* ray.c */
void	ray_init(t_ray *ray, double rayAngle);
void	cal_distance(t_god *god, t_dpable_ray *horz_or_vert);
void	draw_ray(t_god *god);
// void    draw_line(t_god *god, double x1, double y1, double x2, double y2);
// 광선 한줄 그림
void    draw_line(t_god *god, double dx, double dy);
// void	draw_one_ray(t_god *god, double angle);
void	draw_one_ray(t_god *god, double angle, int i);
double	normalize_angle(double angle);


double distance_between_points(double x1, double y1, double x2, double y2);
// void    cal_ray(t_god *god, t_dpable_ray *horz_or_vert);
void    cal_ray(t_god *god, t_dpable_ray *horz_or_vert, int x_adjust, int y_adjust);

void    cal_horz_ray(t_god *god, t_dpable_ray *horz);
void cal_vert_ray(t_god *god, t_dpable_ray *vert);
void fill_3D_color(t_god *god);

int draw_sky(t_god *god, int ray_num, int wall_top_pixel);
int draw_floor(t_god *god, int ray_num, int wall_bottom_pixel);

void	init_info(t_god *god, t_3d_info *info);
int		select_color(t_god *god, t_3d_info *info, int y);

#endif
