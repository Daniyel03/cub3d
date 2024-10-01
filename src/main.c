/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/09/30 13:05:48 by hrother          ###   ########.fr       */
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
	cb->player.pos.x = -1;
	cb->player.pos.y = -1;
	cb->keybinds = NULL;
	cb->mlx = NULL;
}

t_img	init_texture(char *filename, t_cb *cb)
{
	t_img	texture;

	texture.img = mlx_xpm_file_to_image(cb->mlx, filename, &texture.width,
			&texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_length, &texture.endian);
	return (texture);
}

int	hex_atoi(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 48);
	return (c - 87);
}

int	hex_to_int(char *str)
{
	int	res;
	int	power;

	res = 0;
	power = 5;
	str += 2;
	while (*str)
		res += hex_atoi(*str++) * (int)pow((int)16, (int)power--);
	return (res);
}

void	cub3d(char **argv)
{
	t_cb	cb;

	init_struct(&cb);
	parser(&cb, argv);
	// // printf("player: %f, %f\n", cb.player.pos.x, cb.player.pos.y);
	init_mlx(&cb);
	cb.map.textures[0] = init_texture(cb.map.textures_arr[0], &cb);
	cb.map.textures[1] = init_texture(cb.map.textures_arr[1], &cb);
	cb.map.textures[2] = init_texture(cb.map.textures_arr[2], &cb);
	cb.map.textures[3] = init_texture(cb.map.textures_arr[3], &cb);
	cb.map.ceil_color = hex_to_int(cb.map.textures_arr[4]);
	cb.map.floor_color = hex_to_int(cb.map.textures_arr[5]);
	init_keybinds(&cb);
	setup_hooks(&cb);
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