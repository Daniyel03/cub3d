/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:15:28 by hannes            #+#    #+#             */
/*   Updated: 2024/06/28 15:51:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_player(int x, int y, t_cb *cb)
{
	t_vec2	pixel;

	pixel.x = (double) x / MAP_SCALE;
	pixel.y = (double) y / MAP_SCALE;
	return (distance(pixel, cb->player_pos) < (double) MAP_SCALE / 170);
}

void	draw_map(t_cb *cb, int map[10][10], int y_max, int x_max)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x / MAP_SCALE < x_max && y / MAP_SCALE < y_max)
			{
				if (is_player(x, y, cb))
					put_pixel(cb->img, x, y, 0xff0000);
				else if (map[y / MAP_SCALE][x / MAP_SCALE] == 1)
					put_pixel(cb->img, x, y, 0x0000ff);
				else
					put_pixel(cb->img, x, y, 0x00ff00);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cb->mlx, cb->win, cb->img.img, 0, 0);
}
