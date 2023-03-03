/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:06 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/03 10:39:10 by mikim3           ###   ########.fr       */
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
#include "./mlx/mlx.h"

// 1배율은 꽉참
#define MINI_SCALE 1
#define TILE_SIZE 40
// 맵의 행 크기, 파싱을 받을 경우 그 맵의 크기를 구구해해서  ak만들어 줘야 된다.
#define MAP_NUM_ROWS 12
#define MAP_NUM_COLS 20
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

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
// 광선의 갯수 적으면 시야가 이상함? 덜 꼼꼼해짐 // 이 시야 안에서 몇개의 광선으로 내가 보고
// 있는 방향을 나타낼지를 결정함 RAY_COUNT가
// 2개이상 홀수개로 설정해야좋음
# define	RAY_COUNT 799

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
# define WALKSPEED			(2.0)
# define TURNSPEED			(0.02617993878)
# define WALL_STRIP_WIDTH	(1)
# define IS_3D_WALL			(0x663333)
# define VIRTICAL_COLOR		(0x00FF00)
# define HORIZON_COLOR		(0x0000FF)
# define PLAYER_2D_COLOR	(0x000088)
# define SKY_COLOR			(0x444444)
# define FLOOR_COLOR		(0x000000)
# define RAY_COLOR			(0xFF0000)
# define VERT_WALL_COLOR	(0xFFFFFF)
# define HORI_WALL_COLOR	(0xAAAAAA)
// # define RAY_RANGE			(FOV_ANGLE)

# define UPDOWNSPEED		(3)

// t_god으로 합병됨
// typedef struct	s_mlx
// {
// 	void		*mlx;
// 	void		*win;
// }				t_mlx;

typedef struct	s_img
{
	void		*img;//
	int			*data;
	int			bpp; //픽셀 하나(색상 하나)를 표현하는 데 필요한 비트 수
	int			line_size; //
	int			endian; //
	void		*ptr;//mlx_get_data_addr()의 첫번쨰 인자 void *img_ptr로 쓰일 멤버변수
}				t_img;

typedef struct s_player {
	double	x; // 2차원시점 플레이어의 좌우좌표
	double	y; // 상하좌표
	int	thickness; // 두께
	double	rotationAngle;//바라보는 각도 시야각도 그 시야각의 중심위치    값이 0~360 아님
	double	walkSpeed;
	double	turnSpeed;// 바라보는 각도의 조정속도
	double	updown_sight; // 플레이어 위아래
} t_player;


// 파싱한 맵에 대한 정보를 넣어줄 구조체
typedef struct s_map
{
	int		map_rows;
	int		map_cols;
	int		window_width;
	int		window_height;
	int		ray_count;//화면을 꽉채울 적절한 광선의 갯수 계산해서 넣기
	char	**map_matrix;//
}				t_map;

typedef struct s_key
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	right_rotation; // 오른쪽을 바라봐라
	int	left_rotation;
	int	updown_sight; //플레이어의 위아래시야를 올릴지 내릴지
	// int	open_door;
	// int	mouse_on;
}				t_key;

// disposable "일회용"
// 광선을 한개 그릴 때만 유효한 요소들이라는 뜻
typedef struct s_dpable_ray {
    double  xintercept; // 최초로 경계면에서 만나는 지점
    double  yintercept;
    double  xstep;
    double  ystep;
    int     found_wallHit;
    double  wall_hitX;
    double  wall_hitY;
    double  distance;
} t_dpable_ray;


typedef struct s_ray {
    double  ray_angle;
    double  wall_hitX; //광선이 지나가는 길에 벽과 부딪힌 두점중에 가까운점의 x좌표
    double  wall_hitY;
    double  distance; // 그 가까운 좌표의 거리
    int     wasHit_vertical; //광선이 수직선과 처음으로  부딪히면 값이 TRUE 수평선과 처음 부딪히면 FALSE
    int     isRay_facingDown;//광선이 바라보는 방향
    int     isRay_facingUp;
    int     isRay_facingRight;
    int     isRay_facingLeft;
} t_ray;

typedef struct s_god {
	t_player player;
	t_img	img;
	t_key	key;
	t_ray	ray;//광선
	t_map	map;//파싱을 받으면 넣은 맵 구조체 파싱할 사람이 바꿔도 됨
	void	*mlx;
	void	*win;
} t_god;

void	fill_squares(t_img *map, int x, int y, int color);

/* render */
void	render_master(t_god *god); //모든 렌더링을 수행해주는 함수
void	render_map(t_god	*god);
// void	render_map(t_mlx *mlx, t_img *map);
// void	render_player(t_mlx *mlx, t_img *map);
void	render_player(t_god *god);
void	render_3D_project_walls(t_god *god, int ray_num);



void    setting_map_location(int *x, int *y, int x2, int y2);

/* player */
void player_init(t_player *player);
// int    draw_player(t_mlx *mlx, t_player *player, t_img *map);
// int    draw_player(t_god *god);
int    draw_player(t_god *god, t_player *player, t_img *img);
int		update_player(t_god *god);

void		key_init(t_key *key);
int        key_press(int keycode, t_key *key);
int        key_release(int keycode, t_key *key);
int		key_exit(void);

int		is_wall(double x, double y);
// int		check_edge(t_god *god, double x1, double x2, double y1, double y2);

/* ray.c */
void	ray_init(t_ray *ray, double rayAngle);
double	distance_between_points(double x1, double y1, double x2, double y2);
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

int draw_sky(t_god *god, int ray_num, int wall_top_pixel, int color);
int draw_floor(t_god *god, int ray_num, int wall_bottom_pixel, int color);

#endif
