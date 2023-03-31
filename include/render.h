/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:12:44 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 16:45:16 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "struct.h"

/* key event */
# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT			17

//player.c

//render_master.c
int		ft_loop(t_cub *cub);
void	fill_3d_color(t_cub *cub);
void	render_player(t_cub *cub);
void	render_master(t_cub *cub);

//render_wall.c
void	init_info(t_cub *cub, t_3d_info *info);
void	check_wall_direction(t_cub *cub, t_3d_info *info);
int		select_color(t_cub *cub, t_3d_info *info, int idx);
void	render_3d_project_walls(t_cub *cub, int ray_num);

#endif
