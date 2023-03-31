/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:16:07 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 16:44:43 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>
# include "struct.h"

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F  4
# define C  5

// read.c
void	read_file(t_cub *cub, char *filename);
void	read_info(t_cub *cub, int fd);
void	read_map(t_cub *cub, int fd);
char	*get_line_map(int fd);
void	check_type(t_cub *cub, char *line);

//parsing.c
void	parse_texture(t_cub *cub, char *filename, int type);
void	parse_color(t_cub *cub, char *line, int type);
void	parse_map(t_cub *cub, char **str_map);

//check_map.c
void	check_valid_char(t_cub *cub, char **str);
void	check_valid_line(t_cub *cub, char *line, int i, int	*tag);
void	check_around_wall(t_map *map);
void	check_space_pos(t_map *map, int r, int c);

#endif