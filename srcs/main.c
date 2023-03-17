/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:20:35 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/01 21:01:51 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static void main_init(t_god *god)
{
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, god->map.window_width, god->map.window_height, "title");
	// god->img.ptr = mlx_new_image(god->mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));
    // player.img = mlx_new_image(god->mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));

	// 미니맵만 출력해야 할때 는 MINI_SCALE 곱함
	// god->img.ptr = mlx_new_image(god->mlx,
	// 		(int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));

	key_init(&(god->key));
	//god
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
	// t_mlx	mlx;
	// t_img	map;
	// t_img 	player;
	t_god	god; // player, map, t_mlx 등을 합합친  변변수수

	if (ac != 2)
		return (print_error("Input a map's file name."));
	if (!check_extension(av[1]))
		return (print_error("Input the \".cub\" extension file."));
	read_file(&god, av[1]);
	main_init(&god);
	// mlx.mlx = mlx_init();
	// mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "title");
	// map.img = mlx_new_image(mlx.mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));
    // player.img = mlx_new_image(mlx.mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));
	// render_map(&mlx, &map);
    // render_player(&mlx, &map);
    // render_player(&god);
	render_master(&god);
	mlx_loop(god.mlx);
	for (int i = 0; i < god.map.map_cols; i++)
		free(god.map.map_matrix[i]);
	free(god.map.map_matrix);
	mlx_destroy_window(god.mlx, god.win);
	return (0);
}
