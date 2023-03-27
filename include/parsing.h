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
# include "struct.h"

// read.c
void	read_file(t_god *god, char *filename);
void	read_info(t_god *god, int fd);
void	read_map(t_god *god, int fd);
void	check_type(t_god *god, char *line);
void	get_map_info(t_map *map, char **str_map);

//parsing.c
void	parse_texture(t_god *god, char *filename, int type);
void	parse_color(t_god *god, char *line, int type);
int		get_color(char **str_num);
void	parsing_map(t_god *god, char **str_map);
void	fill_map(t_god *god, char *line_map, int i);

//check_map.c
void	check_valid_char(t_god *god, char **str);
void	check_valid_line(t_god *god, char *line, int i, int	*tag);
void	check_around_wall(t_map *map);
void	check_space_pos(t_map *map, int r, int c);

#endif