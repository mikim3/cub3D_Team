/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:16:26 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw_player(t_cub *cub, t_player *player, t_img *img)
{
	int	x;
	int	y;
	int	row;
	int	col;

	setting_map_location(&(cub->map), &x, &y, player->x, player->y);
	update_player(cub);
	row = -(player->thickness) / 2;
	while (row <= player->thickness / 2)
	{
		col = -(player->thickness) / 2;
		while (col <= player->thickness / 2)
		{
			img->data[cub->map.window_width * (y + row) + (x + col)] = \
			PLAYER_2D_COLOR;
			col++;
		}
		row++;
	}
	return (0);
}

// 줄 줄이기 위해 변경
// int	update_player(t_cub *cub)
// {
// 	double	turnDirection = 0;
// 	double	walkDirection = 0;
// 	double	newPlayerX;
// 	double	newPlayerY;
// 	double	moveside = 0.0;

// 	cub->player
// 	// 시선이동
// 	if (cub->key.left == TRUE)
// 	{
// 		moveside = M_PI_2;// 90도 회전한 방향으로
// 		walkDirection = 1.0;// 앞으로이동
// 	}
// 	if (cub->key.right == TRUE)
// 	{
// 		moveside = M_PI_2;
// 		walkDirection = -1.0;
// 	}
// 	// 앞뒤
// 	if (cub->key.up == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = 1;
// 	}
// 	if (cub->key.down == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = -1;
// 	}
// 	if (cub->key.left_rotation == 1)
// 		turnDirection = -1;
// 	if (cub->key.right_rotation == 1)
// 		turnDirection = 1;

// 	cub->player.rotationAngle += turnDirection * cub->player.turnSpeed;
// 	int	moveStep = walkDirection * cub->player.walkSpeed;
// 	newPlayerX = cub->player.x + moveStep * cos(cub->player.rotationAngle - moveside);
// 	newPlayerY = cub->player.y + moveStep * sin(cub->player.rotationAngle - moveside);

// 	// printf("key left == %d  key right == %d key up == %d key down == %d \n",cub->key.left,cub->key.right,cub->key.up,cub->key.down);
// 	// printf("moveStep == %d newPlayerX == %f newPlayerY == %f\n",moveStep, newPlayerX, newPlayerY);
// 	// printf("cos rotationAngle == %f sin rotationAngle %f\n",cos(cub->player.rotationAngle), sin(cub->player.rotationAngle));
// 	// printf("rotationAngle == %f \n",cub->player.rotationAngle);
// 	// printf("walkDirection %f \n",walkDirection);

// 	// (14) 보고 !check_edge(cub, &p1, &p2) && 추가할지 고민하기
// 	// 벽이면 이동 불가
// 	if (!is_wall(&(cub->map), newPlayerX, newPlayerY))
// 	{
// 		//벽아니면 현재좌표를 이동
// 		cub->player.x = newPlayerX;
// 		cub->player.y = newPlayerY;
// 	}
// 	return (0);
// }

int	update_player(t_cub *cub)
{
	double	turnDirection = 0;
	double	walkDirection = 0;
	double	newPlayerX;
	double	newPlayerY;
	double	moveside = 0.0;

	// cub->player
	// 시선이동
	if (cub->key.left == TRUE)
	{
		moveside = M_PI_2;// 90도 회전한 방향으로
		walkDirection = 1.0;// 앞으로이동
	}
	if (cub->key.right == TRUE)
	{
		moveside = M_PI_2;
		walkDirection = -1.0;
	}
	// 앞뒤
	if (cub->key.up == 1)
	{
		moveside = 0.0;
		walkDirection = 1;
	}
	if (cub->key.down == 1)
	{
		moveside = 0.0;
		walkDirection = -1;
	}
	if (cub->key.left_rotation == 1)
		turnDirection = -1;
	if (cub->key.right_rotation == 1)
		turnDirection = 1;

	cub->player.rotationAngle += turnDirection * cub->player.turnSpeed;
	int	moveStep = walkDirection * cub->player.walkSpeed;
	newPlayerX = cub->player.x + moveStep * cos(cub->player.rotationAngle - moveside);
	newPlayerY = cub->player.y + moveStep * sin(cub->player.rotationAngle - moveside);

	// (14) 보고 !check_edge(cub, &p1, &p2) && 추가할지 고민하기
	// 벽이면 이동 불가
	if (!is_wall(&(cub->map), newPlayerX, newPlayerY) &&\
	!check_edge(cub, cub->player.x, cub->player.y, newPlayerX, newPlayerY))
	{
		//벽아니면 현재좌표를 이동
		cub->player.x = newPlayerX;
		cub->player.y = newPlayerY;
	}
	return (0);
}

// static void update_player_movement(t_cub *cub, double *moveside , double *walkDirection, double *turnDirection)
// {
// 	*turnDirection = 0;
// 	*walkDirection = 0;
	

// 	if (cub->key.left == TRUE)
// 	{
// 		moveside = M_PI_2;// 90도 회전한 방향으로
// 		walkDirection = 1.0;// 앞으로이동
// 	}
// 	if (cub->key.right == TRUE)
// 	{
// 		moveside = M_PI_2;
// 		walkDirection = -1.0;
// 	}
// 	// 앞뒤
// 	if (cub->key.up == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = 1;
// 	}
// 	if (cub->key.down == 1)
// 	{
// 		moveside = 0.0;
// 		walkDirection = -1;
// 	}
// 	if (cub->key.left_rotation == 1)
// 		turnDirection = -1;
// 	if (cub->key.right_rotation == 1)
// 		turnDirection = 1;
// }
