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
char    **read_map(int fd);
void    parsing_map(t_god *god, char **str_map);
void    get_map_info(t_map *map, char **str_map);
#endif