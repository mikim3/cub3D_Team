/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:20:35 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/30 20:28:22 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	main(int ac, char **av)
{
	t_god	god;
	int		i;

	if (ac != 2)
	{
		ft_putendl_fd("Input A map's file name.", STDOUT_FILENO);
		return (1);
	}
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
