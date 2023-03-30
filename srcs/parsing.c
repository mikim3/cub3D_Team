/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:16:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/26 20:37:27 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_texture(t_god *god, char *filename, int type)
{
	god->texture[type].width = 0;
	god->texture[type].height = 0;
	god->texture[type].img.img = mlx_xpm_file_to_image(god->mlx, filename, \
	&god->texture[type].width, &god->texture[type].height);
	if (!god->texture[type].img.img)
		exit_error("FAIL to Load Texture");
	god->texture[type].img.data = (int *)mlx_get_data_addr(\
	god->texture[type].img.img, &god->texture[type].img.bpp, \
	&god->texture[type].img.line_size, &god->texture[type].img.endian);
}

void	parse_color(t_god *god, char *line, int type)
{
	int		color;
	char	**str_num;

	str_num = ft_split(line, ',');
	if (!str_num)
		exit_error("ft_split");
	color = get_color(str_num);
	if (type == F)
		god->map.floor_color = color;
	else if (type == C)
		god->map.sky_color = color;
	else
		exit_error("type_error");
	ft_free(str_num);
}

void	parse_map(t_god *god, char **str_map)
{
	int	i;

	get_map_info(&(god->map), str_map);
	god->map.map_matrix = ft_calloc(god->map.map_rows, sizeof(int *));
	if (!god->map.map_matrix)
		exit_error("Fail to calloc");
	i = 0;
	while (i < god->map.map_rows)
	{
		god->map.map_matrix[i] = ft_calloc(god->map.map_cols, sizeof(int));
		if (!god->map.map_matrix[i])
			exit_error("Fail to calloc");
		fill_map(god, str_map[i], i);
		i++;
	}
}
