/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:12:44 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 20:12:45 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "struct.h"

/* key event */
# define X_EVENT_KEY_PRESS			(2)
# define X_EVENT_KEY_RELEASE		(3)
# define X_EVENT_KEY_EXIT			(17)
 
//player.c 에 위치??
void	player_init(t_player *player, double x, double y, char direction);

//render_master.c
int		ft_loop(t_god *god);
void	fill_3D_color(t_god *god);
void	render_player(t_god *god);
void	render_master(t_god *god);

//render_wall.c
void	init_info(t_god *god, t_3d_info *info);
void	check_wall_direction(t_god *god, t_3d_info *info);
int		select_color(t_god *god, t_3d_info *info, int idx);
void	render_3d_project_walls(t_god *god, int ray_num);

#endif
