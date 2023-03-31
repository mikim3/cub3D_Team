/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:16:26 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 16:46:34 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	player_init(t_player *player, double x, double y, char direction)
{
	player->x = (x + 0.5) * TILE_SIZE;
	player->y = (y + 0.5) * TILE_SIZE;
	player->thickness = PLAYER_THICKNESS;
	if (direction == 'N')
		player->rotation_angle = M_PI * 1.5;
	else if (direction == 'E')
		player->rotation_angle = 0;
	else if (direction == 'W')
		player->rotation_angle = M_PI;
	else
		player->rotation_angle = M_PI * 0.5;
	player->walk_speed = WALKSPEED;
	player->turn_speed = TURNSPEED;
}

int	draw_player(t_cub *cub, t_player *player, t_img *img)
{
	int		x;
	int		y;
	int		row;
	int		col;
	t_point	p;

	p.x = player->x;
	p.y = player->y;
	setting_map_location(&(cub->map), &x, &y, p);
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

static void	update_player_movement(t_cub *cub, double *moveside, \
	double *walk_dir)
{
	*moveside = 0;
	*walk_dir = 0;
	if (cub->key.left == TRUE)
	{
		*moveside = M_PI_2;
		*walk_dir = 1.0;
	}
	if (cub->key.right == TRUE)
	{
		*moveside = M_PI_2;
		*walk_dir = -1.0;
	}
	if (cub->key.up == 1)
	{
		*moveside = 0.0;
		*walk_dir = 1;
	}
	if (cub->key.down == 1)
	{
		*moveside = 0.0;
		*walk_dir = -1;
	}
}

static void	update_player_rot(t_cub *cub, double *turn_dir)
{
	*turn_dir = 0;
	if (cub->key.left_rotation == 1)
		*turn_dir = -1;
	if (cub->key.right_rotation == 1)
		*turn_dir = 1;
}

int	update_player(t_cub *cub)
{
	double		turn_dir;
	double		walk_dir;
	double		moveside;
	int			movestep;
	t_d_point	new_p;

	update_player_movement(cub, &moveside, &walk_dir);
	update_player_rot(cub, &turn_dir);
	cub->player.rotation_angle += turn_dir * cub->player.turn_speed;
	movestep = walk_dir * cub->player.walk_speed;
	new_p.x = cub->player.x + movestep * \
	cos(cub->player.rotation_angle - moveside);
	new_p.y = cub->player.y + movestep * \
	sin(cub->player.rotation_angle - moveside);
	if (!is_wall(&(cub->map), new_p.x, new_p.y) && \
	!check_edge(cub, cub->player.x, cub->player.y, new_p))
	{
		cub->player.x = new_p.x;
		cub->player.y = new_p.y;
	}
	return (0);
}
