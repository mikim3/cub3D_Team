/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:16:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_texture(t_cub *cub, char *filename, int type)
{
	cub->texture[type].width = 0;
	cub->texture[type].height = 0;
	cub->texture[type].img.img = mlx_xpm_file_to_image(cub->mlx, filename, \
	&cub->texture[type].width, &cub->texture[type].height);
	if (!cub->texture[type].img.img)
		exit_error("FAIL to Load Texture");
	cub->texture[type].img.data = (int *)mlx_get_data_addr(\
	cub->texture[type].img.img, &cub->texture[type].img.bpp, \
	&cub->texture[type].img.line_size, &cub->texture[type].img.endian);
}

void	parse_color(t_cub *cub, char *line, int type)
{
	int		color;
	char	**str_num;

	str_num = ft_split(line, ',');
	if (!str_num)
		exit_error("ft_split");
	color = get_color(str_num);
	if (type == F)
		cub->map.floor_color = color;
	else if (type == C)
		cub->map.sky_color = color;
	else
		exit_error("type_error");
	ft_free(str_num);
}

void	parse_map(t_cub *cub, char **str_map)
{
	int	i;

	get_map_info(&(cub->map), str_map);
	cub->map.map_matrix = ft_calloc(cub->map.map_rows, sizeof(int *));
	if (!cub->map.map_matrix)
		exit_error("Fail to calloc");
	i = 0;
	while (i < cub->map.map_rows)
	{
		cub->map.map_matrix[i] = ft_calloc(cub->map.map_cols, sizeof(int));
		if (!cub->map.map_matrix[i])
			exit_error("Fail to calloc");
		fill_map(cub, str_map[i], i);
		i++;
	}
}
