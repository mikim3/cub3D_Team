/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:12:37 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 16:45:36 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "struct.h"

//player.c
void	player_init(t_player *player, double x, double y, char direction);
int		draw_player(t_cub *cub, t_player *player, t_img *img);
int		update_player(t_cub *cub);

#endif
