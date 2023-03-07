/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:37:07 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/01 21:04:09 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    key_init(t_key *key)
{

    // 이동
    key->left = 0;
    key->right = 0;
    key->up = 0;
    key->down = 0;

    // 방향
    key->right_rotation = FALSE;
    key->left_rotation = FALSE;
    key->updown_sight = 0;
}

int        key_press(int keycode, t_key *key)
{
    // 이동방향
    if (keycode == KEY_A)
        key->left = 1;
    if (keycode == KEY_D)
        key->right = 1;
    if (keycode == KEY_W)
        key->up = 1;
    if (keycode == KEY_S)
        key->down = 1;

    // 바라보는 방향
    if (keycode == KEY_RIGHT)
        key->right_rotation = TRUE;
    if (keycode == KEY_LEFT)
        key->left_rotation = TRUE;//??
    if (keycode == KEY_UP)
        key->updown_sight = -1;// 다시보기 확인해보기 ??
    if (keycode == KEY_DOWN)
        key->updown_sight = 1; //

    // printf("key press!!!!!!!!! \n");
    if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

int     key_release(int keycode, t_key *key)
{
    if (keycode == KEY_A)
        key->left = 0;
    if (keycode == KEY_D)
        key->right = 0;
    if (keycode == KEY_W)
        key->up = 0;
    if (keycode == KEY_S)
        key->down = 0;

    if (keycode == KEY_RIGHT)
        key->right_rotation = FALSE;
    if (keycode == KEY_LEFT)
        key->left_rotation = FALSE;
    if (keycode == KEY_UP)
        key->updown_sight = 0;
    if (keycode == KEY_DOWN)
        key->updown_sight = 0;
    // printf("key release ????????????????? \n");
    // printf("x:y = %d:%d\n", player->x, player->y);
    if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

// 생각대로 작동안함 사실 key_exit를 따로 만들 필요가 없긴함
int        key_exit(void)
{
    // printf("key_exit \n");
	// exit(0);
    return (0);
}

