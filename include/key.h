/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:55:04 by soylee            #+#    #+#             */
/*   Updated: 2023/03/30 20:12:58 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# include "struct.h"

/* key */
# define KEY_ESC    (53)
# define KEY_W      (13)
# define KEY_A      (0)
# define KEY_S      (1)
# define KEY_D      (2)

# define KEY_LEFT	(123)
# define KEY_RIGHT	(124)
# define KEY_UP 	(126)
# define KEY_DOWN	(125)

//key.c
void	key_init(t_key *key);
int		key_press(int keycode, t_key *key);
int		key_release(int keycode, t_key *key);
int		key_exit(void);


#endif