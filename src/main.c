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
	// cb->texture.img = mlx_new_image(cb->mlx, 100, 100);
	// cb->texture.addr = mlx_get_data_addr(cb->texture.img,
	// &cb->texture.bits_per_pixel, &cb->texture.line_length,
	// &cb->texture.endian);
	// if (cb->texture.img == NULL || cb->texture.addr == NULL)
	// return (exit_cub(cb, "mlx error"), FAILURE);
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

// t_img	init_texture(char *filename, t_cb *cb)
// {
// 	t_img	texture;

// 	texture.img = mlx_xpm_file_to_image(cb->mlx, filename, &texture.width,
// 			&texture.height);
// 	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
// 			&texture.line_length, &texture.endian);
// 	return (texture);
// }

void	cub3d(char **argv)
{
	t_cb	cb;

	init_struct(&cb);
	parser(&cb, argv);
	// // printf("player: %f, %f\n", cb.player.pos.x, cb.player.pos.y);
	// init_mlx(&cb);
	// cb.map.textures[0] = init_texture("maps/textures/grass-block_16.xpm", &cb);
	// cb.map.textures[1] = init_texture("maps/textures/TNT.xpm", &cb);
	// cb.map.textures[2] = init_texture("maps/textures/dimond.xpm", &cb);
	// cb.map.textures[3] = init_texture("maps/textures/stone.xpm", &cb);
	// cb.map.ceil_color = 0x4881b0;
	// cb.map.floor_color = 0x0eb029;
	// // put_pattern(&cb);
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