/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:16:28 by soylee            #+#    #+#             */
/*   Updated: 2023/03/12 15:16:38 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    read_file(t_god *god, char *filename)
{
    int     fd;
    char    **str_map;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_error("Fail to open file.");
    str_map = read_map(fd);
    if (!str_map)
        exit_error("Fail to split map.");
    parsing_map(god, str_map);
}

char    **read_map(int fd)
{
    char    *line;
    char    *gnl_tmp;
    char    *join_tmp;

    line = ft_strdup("");
    while (1)
    {
        gnl_tmp = get_next_line(fd);
        if (!gnl_tmp)
            break ;
        join_tmp = ft_strjoin(line, gnl_tmp);
        free(line);
        free(gnl_tmp);
        line = join_tmp;
    }
    return (ft_split(line, '\n'));
}

void    parsing_map(t_god *god, char **str_map)
{
    int  i;
    int  j;
    int  len;

    get_map_info(&(god->map), str_map);
    god->map.map_matrix = ft_calloc(god->map.map_rows, sizeof(int*));
    if (!god->map.map_matrix)
        exit_error("Fail to calloc");
    i = 0;
    while (i < god->map.map_rows)
    {
        j = 0;
        god->map.map_matrix[i] = ft_calloc(god->map.map_cols, sizeof(int));
        if (!god->map.map_matrix[i])
            exit_error("Fail to calloc");
        len = ft_strlen(str_map[i]);
        while (j < god->map.map_cols)
        {
            if (j >= len || str_map[i][j] == ' ')
                god->map.map_matrix[i][j] = -1;
            else if (str_map[i][j] == '1')
                god->map.map_matrix[i][j] = 1;
            j++;
        }
        i++;
    }
}

void    get_map_info(t_map *map, char **str_map)
{
    int  i;
    int  max;
    int  len;

    i = 0;
    max = -1;
    while (str_map[i])
    {
        len = ft_strlen(str_map[i]);
        if (len == 0)
            exit_error("There is Empty line in map.");
        if (max < len)
            max = len;
        i++;
    }
    if (max == -1)
        exit_error("There is no map.");
    map->map_cols = max;
    map->map_rows = i;
}