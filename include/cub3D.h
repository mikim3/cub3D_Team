/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:39:06 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 13:32:10 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define _USE_MATH_DEFINES
# include <math.h>
# include <float.h>
# include "mlx.h"
# include "libft.h"

# include "struct.h"
# include "key.h"
# include "map.h"
# include "parsing.h"
# include "player.h"
# include "ray.h"
# include "render.h"
# include "utils.h"

# define TILE_SIZE			40
// # define FOV_ANGLE			(60 * (M_PI / 180.0))
# define FOV_ANGLE			(1.047197551)
# define RAY_RANGE          (FOV_ANGLE)

# define TRUE				1
# define FALSE				0

# define MINIMAP_SCALE  	0.25 
# define MAP_LOCATION (RIGHTDOWN_MAP)
# define PLAYER_THICKNESS	6
# define WALKSPEED			1
// # define TURNSPEED			(1.5 * (M_PI / 180))
# define TURNSPEED			0.0261799387799
# define WALL_STRIP_WIDTH	1
# define IS_3D_AREA			0x663333
# define PLAYER_2D_COLOR	0x00AAAA
# define RAY_COLOR			0xFF0000
# define WALL_2D_COLOR		0xFFFFFF 
# define TILE_2D_COLOR		0x000000

#endif
