/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:37:07 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/30 20:11:00 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_init(t_key *key)
{	
	key->left = 0;
	key->right = 0;
	key->up = 0;
	key->down = 0;
	key->right_rotation = FALSE;
	key->left_rotation = FALSE;
}

int	key_press(int keycode, t_key *key)
{
	if (keycode == KEY_A)
		key->left = 1;
	if (keycode == KEY_D)
		key->right = 1;
	if (keycode == KEY_W)
		key->up = 1;
	if (keycode == KEY_S)
		key->down = 1;
	if (keycode == KEY_RIGHT)
		key->right_rotation = TRUE;
	if (keycode == KEY_LEFT)
		key->left_rotation = TRUE;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_key *key)
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
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_exit(void)
{
	exit(0);
	return (0);
}
