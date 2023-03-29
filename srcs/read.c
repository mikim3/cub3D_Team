/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:42:03 by soylee            #+#    #+#             */
/*   Updated: 2023/03/27 20:42:05 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_file(t_god *god, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Fail to open file.");
	read_info(god, fd);
	read_map(god, fd);
	close(fd);
}

void	read_info(t_god *god, int fd)
{
	char	*line;
	int		cnt;
	char	*nl;

	cnt = 0;
	while (cnt < 6)
	{
		line = get_next_line(fd);
		if (!line)
			exit_error("read_info");
		if (ft_strncmp(line, "\n", 2) != 0)
		{
			nl = ft_strrchr(line, '\n');
			if (nl)
				*nl = 0;
			check_type(god, line);
			cnt++;
		}
		free(line);
	}
}

void	read_map(t_god *god, int fd)
{
	char	**str_map;
	char	*line;

	line = get_line_map(fd);
	str_map = ft_split(line, '\n');
	if (!str_map)
		exit_error("Fail to split map.");
	free(line);
	check_valid_char(god, str_map);
	parsing_map(god, str_map);
	check_around_wall(&god->map);
	ft_free(str_map);
}

char	*get_line_map(int fd)
{
	char	*line;
	char	*gnl_tmp;
	char	*join_tmp;

	line = ft_strdup("");
	gnl_tmp = get_next_line(fd);
	while (gnl_tmp && ft_strncmp(gnl_tmp, "\n", 2) == 0)
	{
		free(gnl_tmp);
		gnl_tmp = get_next_line(fd);
	}
	while (gnl_tmp)
	{
		if (ft_strncmp(gnl_tmp, "\n", 2) == 0)
		{
			free(gnl_tmp);
			gnl_tmp = ft_strdup(" \n");
		}
		join_tmp = ft_strjoin(line, gnl_tmp);
		free(line);
		free(gnl_tmp);
		line = join_tmp;
		gnl_tmp = get_next_line(fd);
	}
	return (line);
}

void	check_type(t_god *god, char *line)
{
	static char	*type[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	static int	checked[6];
	int			i;
	int			len;

	i = 0;
	while (i < 6)
	{
		len = 2;
		if (i < 4)
			len = 3;
		if (ft_strncmp(line, type[i], len) == 0)
		{
			if (checked[i])
				exit_error("Duplicated type");
			if (ft_strlen(type[i]) == 3)
				parse_texture(god, line + 3, i);
			else
				parse_color(god, line + 2, i);
			checked[i] = 1;
			return ;
		}
		i++;
	}
	exit_error("Mismatch type");
}

void	get_map_info(t_map *map, char **str_map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = -1;
	while (str_map[i])
	{
		len = ft_strlen(str_map[i]);
		if (max < len)
			max = len;
		i++;
	}
	if (max == -1)
		exit_error("There is no map.");
	map->map_cols = max;
	map->map_rows = i;
	map->window_width = map->map_cols * TILE_SIZE;
	map->window_height = map->map_rows * TILE_SIZE;
	map->ray_count = map->window_width;
}
