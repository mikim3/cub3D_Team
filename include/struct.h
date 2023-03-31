/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:02:22 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 15:34:11 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			line_size;
	int			endian;
	void		*ptr;
}			t_img;

typedef struct s_player {
	double	x;
	double	y;
	int		thickness;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;
	double	turn_direction;
	double	walk_direction;
	double	moveside;
}				t_player;

// 파싱한 맵에 대한 정보를 넣어줄 구조체
typedef struct s_map
{
	int		map_rows;
	int		map_cols;
	int		window_width;
	int		window_height;
	int		ray_count;
	int		**map_matrix;
	int		floor_color;
	int		sky_color;
}				t_map;

//이동 및 방향
typedef struct s_key
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	right_rotation;
	int	left_rotation;
}				t_key;

typedef struct s_dpable_ray {
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		found_wallhit;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
}		t_dpable_ray;

typedef struct s_ray {
	double	ray_angle;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
	int		washit_vertical;
	int		isray_facingdown;
	int		isray_facingup;
	int		isray_facingright;
	int		isray_facingleft;
}		t_ray;

typedef struct s_texture
{
	int		width;
	int		height;
	t_img	img;
}	t_texture;

typedef struct s_cub {
	t_player	player;
	t_img		img;
	t_key		key;
	t_ray		ray;
	t_map		map;
	t_texture	texture[6];
	void		*mlx;
	void		*win;
}	t_cub;

typedef struct s_3d_info
{
	double	correct_distance;
	double	distance_project_plane;
	double	projected_wall_height;
	int		wall_strip_height;
	int		wall_top;
	int		wall_bottom;
	int		correct_wall_top;
	int		correct_wall_bottom;
	int		direction;
}	t_3d_info;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_d_point {
	double	x;
	double	y;
}	t_d_point;

#endif
