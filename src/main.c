/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/06/29 12:31:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>


void	get_map(t_cb *cb, char **argv)
{
	validate_path(cb, argv);
	alloc_array(cb);
}

int	init_mlx(t_cb *cb)
{
	cb->mlx = mlx_init();
	if (!cb->mlx)
		return (-1);
	cb->win = mlx_new_window(cb->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cb->win)
		return (-1);
	cb->img.img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->img.addr = mlx_get_data_addr(cb->img.img, &cb->img.bits_per_pixel,
			&cb->img.line_length, &cb->img.endian);
	if (cb->img.img == NULL || cb->img.addr == NULL)
		return (-1); // --> exit
	return (0);
}


void	init_struct(t_cb *cb)
{
	ft_bzero(cb, sizeof(t_cb));
	ft_bzero(&cb->map, sizeof(t_map));
	cb->player_pos.x = -1;
	cb->player_pos.y = -1;
}

void	cub3d(char **argv)
{
	t_cb	cb;

	// init_struct(&cb);
	get_map(&cb, argv);
	// init_mlx(&cb);
	// init_keybinds(&cb);
	// setup_hooks(&cb);
	// mlx_loop(cb.mlx);
	exit_cub(&cb, "success\n");
}

int	main(int argc, char **argv)
{
	// perror("");
	if (argc == 2)
		cub3d(argv);
	return (0);
}