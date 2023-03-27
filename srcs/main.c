/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:20:35 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/27 18:50:18 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static void main_init(t_god *god)
{
	god->win = mlx_new_window(god->mlx, god->map.window_width, god->map.window_height, "title");
	key_init(&(god->key));
	god->img.ptr = mlx_new_image(god->mlx, god->map.window_width, god->map.window_height);
	god->img.data = (int *)mlx_get_data_addr(god->img.ptr, &(god->img.bpp),
			&(god->img.line_size), &(god->img.endian));
}

void do_exit(void)
{
	system("leaks -q cub3D");
}

int		main(int ac, char **av)
{
	atexit(do_exit);
	t_god	god;

	if (ac != 2)
		return (print_error("Input a map's file name."));
	if (!check_extension(av[1]))
		return (print_error("Input the \".cub\" extension file."));
	god.mlx = mlx_init();
	read_file(&god, av[1]);
	main_init(&god);
	render_master(&god);
	mlx_loop(god.mlx);
	for (int i = 0; i < god.map.map_cols; i++)
		free(god.map.map_matrix[i]);
	free(god.map.map_matrix);
	mlx_destroy_window(god.mlx, god.win);
	return (0);
}
