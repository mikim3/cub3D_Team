/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:03:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// utils.c
void	exit_error(char *msg);
int		check_extension(char *filename);
void	ft_free(char **str);
int		ft_isdigit_str(char *str);
int		is_emptyline(char *line);

// parsing_utils.c
void	get_map_info(t_map *map, char **str_map);
int		get_color(char **str_num);
void	fill_map(t_cub *cub, char *line_map, int i);

#endif