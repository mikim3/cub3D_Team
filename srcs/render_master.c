/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:25:57 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 15:11:33 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_loop(t_cub *cub)
{
	// 3D를 그릴  범위를 결정해주기
	fill_3d_color(cub);
	// 받은 키값에 맞게 플레이어를 옮긴다.
	// 2D 맵 그리기
	render_map(cub);
	// player를 그려준다.
	render_player(cub);
	//미니맵에 광선그리는 겸 3D 맵도 그려주기
	draw_ray(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.ptr, 0, 0);
	return (0);
}

void	fill_3d_color(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y++ < cub->map.window_height)
	{
		x = 0;
		while (x++ < cub->map.window_width)
		{
			cub->img.data[cub->map.window_width * y + x] = IS_3D_AREA;
		}
	}
}

void	render_player(t_cub *cub)
{
	draw_player(cub, &(cub->player), &cub->img);
}

void	player_init(t_player *player, double x, double y, char direction)
{
	player->x = (x + 0.5) * TILE_SIZE;
	player->y = (y + 0.5) * TILE_SIZE;
	player->thickness = PLAYER_THICKNESS;
	if (direction == 'N') //위
		player->rotation_angle = M_PI * 1.5;
	else if (direction == 'E') //오른쪽
		player->rotation_angle = 0;
	else if (direction == 'W') //왼쪽
		player->rotation_angle = M_PI;
	else //아래
		player->rotation_angle = M_PI * 0.5;
	player->walk_speed = WALKSPEED;
	player->turn_speed = TURNSPEED;
}

void	render_master(t_cub *cub)
{
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, (1L << 0), &key_press, &(cub->key));
	mlx_hook(cub->win, X_EVENT_KEY_RELEASE, (1L << 1), \
		&key_release, &(cub->key));
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, &key_exit, cub);
	mlx_loop_hook(cub->mlx, ft_loop, cub);
}
