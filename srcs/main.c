/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:20:35 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/28 09:51:48 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void main_init(t_god *god)
// {
// 	// god->mlx = mlx_init();
// 	god->win = mlx_new_window(god->mlx, god->map.window_width, god->map.window_height, "title");
// 	// god->img.ptr = mlx_new_image(god->mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));
// 	// player.img = mlx_new_image(god->mlx, (int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));

// 	// 미니맵만 출력해야 할때 는 MINI_SCALE 곱함
// 	// god->img.ptr = mlx_new_image(god->mlx,
// 	// 		(int)(MINI_SCALE * WINDOW_WIDTH), (int)(MINI_SCALE * WINDOW_HEIGHT));

// 	key_init(&(god->key));
// 	//god
// 	god->img.ptr = mlx_new_image(god->mlx, god->map.window_width, god->map.window_height);
// 	god->img.data = (int *)mlx_get_data_addr(god->img.ptr, &(god->img.bpp),
// 			&(god->img.line_size), &(god->img.endian));
// }

static void	main_init(t_god *god)
{
	god->win = mlx_new_window(god->mlx, god->map.window_width, \
	god->map.window_height, "title");
	key_init(&(god->key));
	god->img.ptr = mlx_new_image(god->mlx, god->map.window_width, \
	god->map.window_height);
	god->img.data = (int *)mlx_get_data_addr(god->img.ptr, &(god->img.bpp),
			&(god->img.line_size), &(god->img.endian));
}

void	do_exit(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_god	god;
	int		i;

	atexit(do_exit);
	if (ac != 2)
		exit_error("Input a map's file name.");
	if (!check_extension(av[1]))
		exit_error("Input the \".cub\" extension file.");
	god.mlx = mlx_init();
	read_file(&god, av[1]);
	main_init(&god);
	render_master(&god);
	mlx_loop(god.mlx);
	i = 0;
	while (god.map.map_matrix[i])
	{
		free(god.map.map_matrix[i]);
		i++;
	}
	free(god.map.map_matrix);
	mlx_destroy_window(god.mlx, god.win);
	return (0);
}

// int main()
// {
// 	void *mlx = mlx_init();
// 	// void *win = mlx_new_window(mlx, 64, 64, "mlx_title");
// 	// void *img = mlx_new_image(mlx, 64, 64);
// 	int w, h;
// 	void *texture = mlx_xpm_file_to_image(mlx, "./asset/CRATE_2A.xpm", &w, &h);
// 	if (!texture)
// 		printf("ERROR\n");
// }
