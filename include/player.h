/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:12:37 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 20:12:38 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "struct.h"

//player.c
int	draw_player(t_god *god, t_player *player, t_img *img);
int	update_player(t_god *god);

#endif
