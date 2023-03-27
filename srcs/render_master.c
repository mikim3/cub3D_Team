/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:25:57 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 11:44:58 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 그리는 녀석들은 반복을 해줘야 한다.
// 그렇지 않으면 미리 그려져 있는 배경에 캐릭터가 움직임을 반복하면 그 플레이어의 그 전 위치가 맵위에
// 계속 남아 있을 것이다. 무엇을 그리든 마찬가지다.
int	 ft_loop(t_god *god)
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
void fill_3D_color(t_god *god)
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

// void player_init(t_player *player, t_map *map)
// {
// 	player->x = map->window_width / 2;
// 	player->y = map->window_height / 2;
// 	player->thickness = PLAYER_THICKNESS;
// 	player->rotationAngle = M_PI / 2; // 0도가 오른쪽 90도면 아래
// 	player->walkSpeed = 1;
// 	player->turnSpeed = 1.5 * (M_PI / 180); //
// }

void player_init(t_player *player, double x, double y, char direction)
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


// 3D 구역을 그리는 함수
// 거리와 반비례하며 distance_project_plane을 곱하여 적절한 높이를 가지게 만들수 있다.
// render_3D_project_walls()가 한번 실행될  때마다  화면 왼쪽부터
// 이 함수가 호출될때 한줄씩  3D화면이 그려짐
void render_3D_project_walls(t_god *god, int ray_num)
{
	t_3d_info info;
	// 지금 부채꼴 모양으로 시야를 받아들이기 떄문에 끝에 있는 부분(화면의 왼쪽과 오른쪽)과
	// 그 부채꼴에 중간 부분은 차이가 있을수 밖에 없다 그래서 세상이 굴곡저 보인다.(어안렌즈 효과)
	// 이를 해결하기위해 correct_distance로

	// 벽에 딱 붙었을때 벽뒤가 보이는 버그 고침
	if (god->ray.distance == 0)
		god->ray.distance = 0.01;
	
	init_info(god, &info);
	for (int y = info.correct_wall_top; y < info.correct_wall_bottom; y++)
		for (int x = 0; x < WALL_STRIP_WIDTH; x++)
			if (god->img.data[god->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] == IS_3D_AREA)
				god->img.data[god->map.window_width * y + (x + ray_num * WALL_STRIP_WIDTH)] = select_color(god, &info, y);
	draw_floor(god, ray_num, info.correct_wall_bottom);
	draw_sky(god, ray_num, info.correct_wall_top);
}

int		select_color(t_god *god, t_3d_info *info, int y)
{
	int r;
	int c;
	if (info->direction == WE || info->direction == EA)
		c = ((int)god->ray.wall_hitY % TILE_SIZE);
	else
		c = ((int)god->ray.wall_hitX % TILE_SIZE);
	c *= god->texture[info->direction].width / TILE_SIZE;
	r = (y - info->wall_top) * god->texture[info->direction].height / info->wallStripHeight;
	return (god->texture[info->direction].img.data[r * god->texture[info->direction].width + c]);
}

void	init_info(t_god *god, t_3d_info *info)
{
	info->correct_distance = god->ray.distance * cos(god->ray.ray_angle - god->player.rotationAngle);
	//투영면까지의 거리
	info->distance_project_plane = (god->map.window_width / 2) / tan(FOV_ANGLE / 2);
	//투영면에 투사된 벽의 높이입니다.
	info->projected_wall_height = (TILE_SIZE / info->correct_distance) * info->distance_project_plane;
	//벽 스트립의 높이입니다. 
	info->wallStripHeight = (int)info->projected_wall_height;

	// 벽 스트립의 상단 픽셀 위치입니다.
	info->wall_top = (god->map.window_height / 2) - (info->wallStripHeight / 2);
	info->correct_wall_top = info->wall_top;
	if (info->wall_top < 0)
		info->correct_wall_top = 0;

	//벽 스트립의 하단 픽셀 위치입니다.
	info->wall_bottom = (god->map.window_height / 2) + (info->wallStripHeight / 2);
	info->correct_wall_bottom = info->wall_bottom;
	if (info->wall_top > god->map.window_height)
		info->correct_wall_bottom = god->map.window_height - 1;

	if (god->ray.wasHit_vertical == TRUE && (god->player.x - god->ray.wall_hitX) > 0)
		info->direction = WE;
	else if (god->ray.wasHit_vertical == TRUE)
		info->direction = EA;
	else if ((god->player.y - god->ray.wall_hitY) > 0)
		info->direction = NO;
	else
		info->direction = SO;

}
void	render_master(t_god *god)
{
	// player_init(&(god->player), &god->map); // 사용자 위치 초기화

	//키누를 때 어떤 함수를 사용할지 결정
	mlx_hook(god->win, X_EVENT_KEY_PRESS, (1L << 0), &key_press, &(god->key));
	mlx_hook(god->win, X_EVENT_KEY_RELEASE, (1L << 1), &key_release, &(god->key));

	// X_EVENT_KEY_EXIT 제대로 작동안함 사실 따로 만들 필요 없긴함
	// mlx_hook(god->win, X_EVENT_KEY_EXIT, 0, &key_exit, god);


	// 이벤트 발생하지 않을시 mlx_loop_hook의 ft_loop 사용
	mlx_loop_hook(god->mlx, ft_loop, god);
	// usleep(5000);
}
