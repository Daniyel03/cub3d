/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/07/01 13:05:46 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>



void	get_map(t_cb *cb, char **argv)
{
	int	valid;

	validate_path(cb, argv);
	alloc_array(cb);
	valid = flood_fill(cb);
	print_map(cb->map);
	print_cord(cb);
	printf("valid map: %d\n", valid);
}

int	init_mlx(t_cb *cb)
{
	cb->mlx = mlx_init();
	if (!cb->mlx)
		return (exit_cub(cb, "mlx error"), FAILURE);
	cb->win = mlx_new_window(cb->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cb->win)
		return (exit_cub(cb, "mlx error"), FAILURE);
	cb->img.img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->img.addr = mlx_get_data_addr(cb->img.img, &cb->img.bits_per_pixel,
			&cb->img.line_length, &cb->img.endian);
	if (cb->img.img == NULL || cb->img.addr == NULL)
		return (exit_cub(cb, "mlx error"), FAILURE);
	cb->img.width = WIDTH;
	cb->img.height = HEIGHT;
	return (0);
}

void	init_struct(t_cb *cb)
{
	ft_bzero(cb, sizeof(t_cb));
	ft_bzero(&cb->map, sizeof(t_map));
	// cb->cords = malloc(sizeof(t_valid_cords));
	// ft_bzero(cb->cords, sizeof(t_valid_cords));
	cb->player.pos.x = -1;
	cb->player.pos.y = -1;
	cb->keybinds = NULL;
	cb->mlx = NULL;
}

void	cub3d(char **argv)
{
	t_cb	cb;

	init_struct(&cb);
	get_map(&cb, argv);
	// printf("player: %f, %f\n", cb.player.pos.x, cb.player.pos.y);
	print_map(cb.map);
	init_mlx(&cb);
	init_keybinds(&cb);
	cb.texture.img = mlx_xpm_file_to_image(cb.mlx, "grass-block_16.xpm", &cb.texture.width, &cb.texture.height);
	cb.texture.addr = mlx_get_data_addr(cb.texture.img, &cb.texture.bits_per_pixel,
			&cb.texture.line_length, &cb.texture.endian);
	mlx_put_image_to_window(cb.mlx, cb.win, cb.texture.img, 0, 0);
	// setup_hooks(&cb);
	mlx_loop(cb.mlx);
	exit_cub(&cb, "success\n");
}

int	main(int argc, char **argv)
{
	// perror("");
	if (argc == 2)
		cub3d(argv);
	return (0);
}