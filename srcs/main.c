/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:20:35 by mikim3            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	main_init(t_cub *cub)
{
	cub->win = mlx_new_window(cub->mlx, cub->map.window_width, \
	cub->map.window_height, "title");
	key_init(&(cub->key));
	cub->img.ptr = mlx_new_image(cub->mlx, cub->map.window_width, \
	cub->map.window_height);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.ptr, &(cub->img.bpp),
			&(cub->img.line_size), &(cub->img.endian));
}

int	main(int ac, char **av)
{
	t_cub	cub;
	int		i;

	if (ac != 2)
	{
		ft_putendl_fd("Input A map's file name.", STDOUT_FILENO);
		return (1);
	}
	cub.mlx = mlx_init();
	read_file(&cub, av[1]);
	main_init(&cub);
	render_master(&cub);
	mlx_loop(cub.mlx);
	i = 0;
	while (cub.map.map_matrix[i])
	{
		free(cub.map.map_matrix[i]);
		i++;
	}
	free(cub.map.map_matrix);
	mlx_destroy_window(cub.mlx, cub.win);
	return (0);
}
