/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:55:04 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 20:55:06 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# include "struct.h"

//key.c
void	key_init(t_key *key);
int		key_press(int keycode, t_key *key);
int		key_release(int keycode, t_key *key);

#endif