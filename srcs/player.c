/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:16:26 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/29 11:41:45 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw_player(t_god *god, t_player *player, t_img *img)
{
	int	x;
	int	y;
	int	row;
	int	col;

	setting_map_location(&(god->map), &x, &y, player->x, player->y);
	update_player(god);
	row = -(player->thickness) / 2;
	while (row <= player->thickness / 2)
	{
		col = -(player->thickness) / 2;
		while (col <= player->thickness / 2)
		{
			img->data[god->map.window_width * (y + row) + (x + col)] = \
			PLAYER_2D_COLOR;
			col++;
		}
		row++;
	}
	return (0);
}

// 줄 줄이기 위해 변경
// int	update_player(t_god *god)
// {
// 	double	turnDirection = 0;
// 	double	walkDirection = 0;
// 	double	newPlayerX;
// 	double	newPlayerY;
// 	double	moveside = 0.0;

// 	god->player
// 	// 시선이동
// 	if (god->key.left == TRUE)
// 	{
// 		moveside = M_PI_2;// 90도 회전한 방향으로
// 		walkDirection = 1.0;// 앞으로이동
// 	}
// 	if (god->key.right == TRUE)
// 	{
// 		moveside = M_PI_2;
// 		walkDirection = -1.0;
// 	}
// 	// 앞뒤
// 	if (god->key.up == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = 1;
// 	}
// 	if (god->key.down == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = -1;
// 	}
// 	if (god->key.left_rotation == 1)
// 		turnDirection = -1;
// 	if (god->key.right_rotation == 1)
// 		turnDirection = 1;

// 	god->player.rotationAngle += turnDirection * god->player.turnSpeed;
// 	int	moveStep = walkDirection * god->player.walkSpeed;
// 	newPlayerX = god->player.x + moveStep * cos(god->player.rotationAngle - moveside);
// 	newPlayerY = god->player.y + moveStep * sin(god->player.rotationAngle - moveside);

// 	// printf("key left == %d  key right == %d key up == %d key down == %d \n",god->key.left,god->key.right,god->key.up,god->key.down);
// 	// printf("moveStep == %d newPlayerX == %f newPlayerY == %f\n",moveStep, newPlayerX, newPlayerY);
// 	// printf("cos rotationAngle == %f sin rotationAngle %f\n",cos(god->player.rotationAngle), sin(god->player.rotationAngle));
// 	// printf("rotationAngle == %f \n",god->player.rotationAngle);
// 	// printf("walkDirection %f \n",walkDirection);

// 	// (14) 보고 !check_edge(god, &p1, &p2) && 추가할지 고민하기
// 	// 벽이면 이동 불가
// 	if (!is_wall(&(god->map), newPlayerX, newPlayerY))
// 	{
// 		//벽아니면 현재좌표를 이동
// 		god->player.x = newPlayerX;
// 		god->player.y = newPlayerY;
// 	}
// 	return (0);
// }

int	update_player(t_god *god)
{
	double	turnDirection = 0;
	double	walkDirection = 0;
	double	newPlayerX;
	double	newPlayerY;
	double	moveside = 0.0;

	// god->player
	// 시선이동
	if (god->key.left == TRUE)
	{
		moveside = M_PI_2;// 90도 회전한 방향으로
		walkDirection = 1.0;// 앞으로이동
	}
	if (god->key.right == TRUE)
	{
		moveside = M_PI_2;
		walkDirection = -1.0;
	}
	// 앞뒤
	if (god->key.up == 1)
	{
		moveside = 0.0;
		walkDirection = 1;
	}
	if (god->key.down == 1)
	{
		moveside = 0.0;
		walkDirection = -1;
	}
	if (god->key.left_rotation == 1)
		turnDirection = -1;
	if (god->key.right_rotation == 1)
		turnDirection = 1;

	god->player.rotationAngle += turnDirection * god->player.turnSpeed;
	int	moveStep = walkDirection * god->player.walkSpeed;
	newPlayerX = god->player.x + moveStep * cos(god->player.rotationAngle - moveside);
	newPlayerY = god->player.y + moveStep * sin(god->player.rotationAngle - moveside);

	// (14) 보고 !check_edge(god, &p1, &p2) && 추가할지 고민하기
	// 벽이면 이동 불가
	if (!is_wall(&(god->map), newPlayerX, newPlayerY) && !check_edge(god, god->player.x, god->player.y, newPlayerX, newPlayerY))
	{
		//벽아니면 현재좌표를 이동
		god->player.x = newPlayerX;
		god->player.y = newPlayerY;
	}
	return (0);
}

// static void update_player_movement(t_god *god, double *moveside , double *walkDirection, double *turnDirection)
// {
// 	*turnDirection = 0;
// 	*walkDirection = 0;
	

// 	if (god->key.left == TRUE)
// 	{
// 		moveside = M_PI_2;// 90도 회전한 방향으로
// 		walkDirection = 1.0;// 앞으로이동
// 	}
// 	if (god->key.right == TRUE)
// 	{
// 		moveside = M_PI_2;
// 		walkDirection = -1.0;
// 	}
// 	// 앞뒤
// 	if (god->key.up == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = 1;
// 	}
// 	if (god->key.down == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = -1;
// 	}
// 	if (god->key.left_rotation == 1)
// 		turnDirection = -1;
// 	if (god->key.right_rotation == 1)
// 		turnDirection = 1;
// }
