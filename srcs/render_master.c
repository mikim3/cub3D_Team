/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:25:57 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/30 20:12:27 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_loop(t_god *god)
{
	// 3D를 그릴  범위를 결정해주기
	fill_3D_color(god);
	// 받은 키값에 맞게 플레이어를 옮긴다.
	// 2D 맵 그리기
	render_map(god);
	// player를 그려준다.
	render_player(god);

	//미니맵에 광선그리는 겸 3D 맵도 그려주기
	draw_ray(god);

	// mlx윈도우에 새로운 이미지를 넣어주는 함수
	// 4,5번째 인자는 그림을 그리기 시작하는 좌표 0,0 이면 윈도우 왼쪽위에서 시작
	mlx_put_image_to_window(god->mlx, god->win, god->img.ptr, 0, 0);
	return (0);
}

//미니맵을 제제외외한  범범위위인  3D를 표현할 범위를 특정색으로 초기화한다.
void	fill_3D_color(t_god *god)
{
	for (int y = 0; y < god->map.window_height; y++)
	{
 	   for (int x = 0; x < god->map.window_width; x++)
			god->img.data[god->map.window_width * y + x] = IS_3D_AREA;
	}
}

void render_player(t_god *god)
{
	draw_player(god,&(god->player),&god->img);
}

void	player_init(t_player *player, double x, double y, char direction)
{
	player->x = (x + 0.5) * TILE_SIZE;
	player->y = (y + 0.5) * TILE_SIZE;
	player->thickness = PLAYER_THICKNESS;
	// 0도가 오른쪽 90도면 아래
	if (direction == 'N') //위
		player->rotationAngle = M_PI * 1.5;
	else if (direction == 'E') //오른쪽
		player->rotationAngle = 0;
	else if (direction == 'W') //왼쪽
		player->rotationAngle = M_PI;
	else //아래
		player->rotationAngle = M_PI * 0.5;
	player->walkSpeed = WALKSPEED;
	player->turnSpeed = TURNSPEED;
}

void	render_master(t_god *god)
{
	// player_init(&(god->player), &god->map); // 사용자 위치 초기화

	//키누를 때 어떤 함수를 사용할지 결정
	mlx_hook(god->win, X_EVENT_KEY_PRESS, (1L << 0), &key_press, &(god->key));
	mlx_hook(god->win, X_EVENT_KEY_RELEASE, (1L << 1), &key_release, &(god->key));
	mlx_hook(god->win, X_EVENT_KEY_EXIT, 0, &key_exit, god);

	// X_EVENT_KEY_EXIT 제대로 작동안함 사실 따로 만들 필요 없긴함
	// mlx_hook(god->win, X_EVENT_KEY_EXIT, 0, &key_exit, god);


	// 이벤트 발생하지 않을시 mlx_loop_hook의 ft_loop 사용
	mlx_loop_hook(god->mlx, ft_loop, god);
	// usleep(5000);
}
