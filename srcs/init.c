/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:47:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 18:58:19 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_init(t_key *key)
{	
	// 이동
	key->left = 0;
	key->right = 0;
	key->up = 0;
	key->down = 0;

	// 방향
	key->right_rotation = FALSE;
	key->left_rotation = FALSE;
}

void	ray_init(t_ray *ray, double rayAngle)
{
	ray->ray_angle = normalize_angle(rayAngle);
	// ray->ray_angle = rayAngle;
	ray->wall_hitX = 0;
	ray->wall_hitY = 0;
	ray->distance = 0;
	ray->wasHit_vertical = FALSE;

	// ray->ray_angle 광선의 진행하는 각도에 따라서 isRay_facing~~를 정해준다.
	// 위왼쪽 위오른쪽 아래왼쪽 아래오른쪽 이렇게 값을 가질수 있는거임
	ray->isRay_facingDown = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->isRay_facingUp = !ray->isRay_facingDown;
	ray->isRay_facingRight = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI;
	ray->isRay_facingLeft = !ray->isRay_facingRight;
}

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
