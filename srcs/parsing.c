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

void    read_file(t_god *god, char *filename)
{
    int     fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_error("Fail to open file.");
    read_info(god, fd);
    read_map(god, fd);
    close(fd);
}

void    read_info(t_god *god, int fd)
{
    char    *line;
    int     cnt;

    cnt = 0;
    while (cnt < 6)
    {
        line = get_next_line(fd);
        if (!line)
            exit_error("read_info");
        if (ft_strlen(line) == 0)
            continue ;
        check_type(god, line);
        free(line);
        cnt++;
    }
}

void    check_type(t_god *god, char * line)
{
    static char *type[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
    static int  checked[6];
    int         i;

    i = 0;
    while (i < 6)
    {
        if (ft_strlen(type[i]) == 3 && ft_strncmp(line, type[i], 3) == 0)
        {
            if (checked[i])
                exit_error("Duplicated type");
            parse_texture(god, line + 3, i);
            checked[i] = 1;
            return ;
        }
        else if (ft_strlen(type[i]) == 2 && ft_strncmp(line, type[i], 2) == 0)
        {
            if (checked[i])
                exit_error("Duplicated type");
            parse_color(god, line + 2, i);
            checked[i] = 1;
            return ;
        }
        i++;
    }
    exit_error("Mismatch type");
}

void    parse_texture(t_god *god, char *filename, int type)
{
    char*  nl = ft_strrchr(filename, '\n');
    *nl = 0;
    god->texture[type].width = 0;god->texture[type].height = 0;
    god->texture[type].img.img = mlx_xpm_file_to_image(god->mlx, filename, &god->texture[type].width, &god->texture[type].height);
    if (!god->texture[type].img.img)
        exit_error("FAIL to Load Texture");
    god->texture[type].img.data = (int*)mlx_get_data_addr(god->texture[type].img.img, &god->texture[type].img.bpp,&god->texture[type].img.line_size,&god->texture[type].img.endian);
}

void    parse_color(t_god *god, char *line, int type)
{
    int color;
    char **str_num;
    int    num;

    line[ft_strlen(line) - 1] = 0;
    str_num = ft_split(line, ',');
    if (!str_num)
        exit_error("ft_split");
    color = 0;
    for (int i = 0; i < 3; i++)
    {
        if (!str_num[i])
            exit_error("lack of color");
        color <<= 8;
        num = ft_atoi(str_num[i]);
        if (num == 0 && ft_strncmp(str_num[i], "0", 1))
            exit_error("non-digit");
        color |= num;
    }
    if (type == F)
    {
        god->map.floor_color = color;
    }
    else if (type == C)
    {
        god->map.sky_color = color;
    }
    else
        exit_error("type_error");
    for (int i = 0; str_num[i]; i++)
        free(str_num[i]);
    free(str_num);
}

void    read_map(t_god *god, int fd)
{
    char    *line;
    char    *gnl_tmp;
    char    *join_tmp;
    char    **str_map;

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
    str_map = ft_split(line, '\n');
    if (!str_map)
        exit_error("Fail to split map.");
    free(line);
    check_valid_char(god, str_map);
    parsing_map(god, str_map);
    check_around_wall(&god->map);
    for(int i = 0; str_map[i]; i++)
        free(str_map[i]);
    free(str_map);
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
    map->window_width = map->map_cols * TILE_SIZE;
    map->window_height = map->map_rows * TILE_SIZE;
    map->ray_count = map->window_width;
}
