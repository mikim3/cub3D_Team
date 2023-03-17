/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:16:07 by soylee            #+#    #+#             */
/*   Updated: 2023/03/12 15:16:18 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
#include "struct.h"

void    read_file(t_god *god, char *filename);
void    read_map(t_god *god, int fd);
void    parsing_map(t_god *god, char **str_map);
void    get_map_info(t_map *map, char **str_map);
void    check_valid_char(t_god *god, char **str);
void    check_around_wall(t_map *map);
void    check_space_pos(t_map *map, int r, int c);
#endif