/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:16:26 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/03 13:02:44 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

// player위치에 맞게 player그리기
// (맵이 쭉 그려지고 그 뒤에 사용자 그림)
// (8) 에서 함수 바꿈
// int    draw_player(t_god *god)
// {

// 	for (int row = -(god->player.thickness) / 2; row <= (god->player.thickness) / 2; row++)
// 	{
// 		for (int col = -(god->player.thickness) / 2; col <= (god->player.thickness) / 2; col++)
// 		{
// 			god->img.data[(int)(MINI_SCALE * (WINDOW_WIDTH * ((int)god->player.y + row) + ((int)god->player.x + col)))] = 0x0000FF;
// 		}
// 	}
// 	return (0);
// }

//
int    draw_player(t_god *god, t_player *player, t_img *img)
{
    int x;
    int y;

    setting_map_location(&x, &y, player->x, player->y);
    update_player(god);
    // 플레이어 중앙점을 중심으로 그림
	for (int row = -(player->thickness) / 2; row <= (player->thickness) / 2; row++)
    {
        for (int col = -(player->thickness) / 2; col <= (player->thickness) / 2; col++)
        {
            img->data[WINDOW_WIDTH * (y + row) + (x + col)] = PLAYER_2D_COLOR;
        }
    }
    return (0);
}

int	update_player(t_god *god)
{
	double	turnDirection = 0;
	double	walkDirection = 0;
	double	newPlayerX;
	double	newPlayerY;
	double	moveside = 0.0;

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
		walkDirection = 1;
		moveside = 0.0;// 90도 회전한 방향으로
	}
	if (god->key.down == 1)
	{
		walkDirection = -1;
		moveside = 0.0;// 90도 회전한 방향으로
	}
	if (god->key.left_rotation == 1)
		turnDirection = -1;
	if (god->key.right_rotation == 1)
		turnDirection = 1;

	god->player.rotationAngle += turnDirection * god->player.turnSpeed;
	//
	int	moveStep = walkDirection * god->player.walkSpeed;
	newPlayerX = god->player.x + moveStep * cos(god->player.rotationAngle - moveside);
	newPlayerY = god->player.y + moveStep * sin(god->player.rotationAngle - moveside);

	printf("key left == %d  key right == %d key up == %d key down == %d \n",god->key.left,god->key.right,god->key.up,god->key.down);
	printf("moveStep == %d newPlayerX == %f newPlayerY == %f\n",moveStep, newPlayerX, newPlayerY);
	printf("cos rotationAngle == %f sin rotationAngle %f\n",cos(god->player.rotationAngle), sin(god->player.rotationAngle));
	printf("rotationAngle == %f \n",god->player.rotationAngle);
	printf("walkDirection %f \n",walkDirection);

	// (14) 보고 !check_edge(god, &p1, &p2) && 추가할지 고민하기
	// 벽이면 이동 불가
	if (!is_wall(newPlayerX, newPlayerY))
	{
		//벽아니면 현재좌표를 이동
		god->player.x = newPlayerX;
		god->player.y = newPlayerY;
	}

	// 시야 이동
	god->player.updown_sight += UPDOWNSPEED * god->key.updown_sight;
	// 시야이동 리미트
	if (god->player.updown_sight > WINDOW_HEIGHT / 5)
		god->player.updown_sight = WINDOW_HEIGHT / 5;
	if (god->player.updown_sight < - WINDOW_HEIGHT / 5)
		god->player.updown_sight = - WINDOW_HEIGHT / 5;

	return (0);
}
