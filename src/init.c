/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:35:43 by hrother           #+#    #+#             */
/*   Updated: 2024/10/05 12:03:45 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_cb *cb)
{
	cb->mlx = mlx_init();
	if (!cb->mlx)
		exit_cub(cb, "mlx error", 1);
	cb->win = mlx_new_window(cb->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cb->win)
		exit_cub(cb, "mlx error", 1);
	cb->img.img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->img.addr = mlx_get_data_addr(cb->img.img, &cb->img.bits_per_pixel,
			&cb->img.line_length, &cb->img.endian);
	if (cb->img.img == NULL || cb->img.addr == NULL)
		exit_cub(cb, "mlx error", 1);
	cb->img.width = WIDTH;
	cb->img.height = HEIGHT;
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
	if (!texture.img)
		return (texture.addr = NULL, texture);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_length, &texture.endian);
	return (texture);
}
