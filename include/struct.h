/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:02:22 by soylee            #+#    #+#             */
/*   Updated: 2023/03/25 20:40:53 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

	double	turnDirection;
	double	walkDirection;
	double	moveside;
} t_player;

// 파싱한 맵에 대한 정보를 넣어줄 구조체
typedef struct s_map
{
	int		map_rows;
	int		map_cols;
	int		window_width; // 윈도우의 가로넓이 보통 800
	int		window_height; //윈도우의 세로 높이 보통 480
	int		ray_count;//화면을 꽉채울 적절한 광선의 갯수 계산해서 넣기
	char	**map_matrix;//
	int		floor_color;
	int		sky_color;
}				t_map;

typedef struct s_key
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	right_rotation; // 오른쪽을 바라봐라
	int	left_rotation;
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
    double  distance; // 그 가까운 좌표의 거리 광선이 즉 부딪힌 벽과의 거리
    int     wasHit_vertical; //광선이 수직선과 처음으로  부딪히면 값이 TRUE 수평선과 처음 부딪히면 FALSE
    int     isRay_facingDown;//광선이 바라보는 방향
    int     isRay_facingUp;
    int     isRay_facingRight;
    int     isRay_facingLeft;
} t_ray;

typedef struct s_texture
{
	int		width;
	int		height;
	void	*texture;
}	t_texture;

typedef enum e_info
{
    NO, SO, WE, EA, F, C
} t_info;

typedef struct s_god {
	t_player player;
	t_img	img;
	t_key	key;
	t_ray	ray;//광선
	t_map	map;
	t_texture	texture[6];
	void	*mlx;
	void	*win;
} t_god;

#endif