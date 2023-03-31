/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:42:03 by soylee            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_file(t_cub *cub, char *filename)
{
	int	fd;

	if (!check_extension(filename))
		exit_error("Input the \".cub\" extension file.");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Fail to open file.");
	read_info(cub, fd);
	read_map(cub, fd);
	close(fd);
}

void	read_info(t_cub *cub, int fd)
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
			check_type(cub, line);
			cnt++;
		}
		free(line);
	}
}

void	read_map(t_cub *cub, int fd)
{
	char	**str_map;
	char	*line;

	line = get_line_map(fd);
	str_map = ft_split(line, '\n');
	if (!str_map)
		exit_error("Fail to split map.");
	free(line);
	check_valid_char(cub, str_map);
	parse_map(cub, str_map);
	check_around_wall(&cub->map);
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

void	check_type(t_cub *cub, char *line)
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
				parse_texture(cub, line + 3, i);
			else
				parse_color(cub, line + 2, i);
			checked[i] = 1;
			return ;
		}
		i++;
	}
	exit_error("Mismatch type");
}
