/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/28 16:51:19 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_player(int x, int y, t_vec2 player_pos)
{
	t_vec2	pixel;

	pixel.x = (double) x / MAP_SCALE;
	pixel.y = (double) y / MAP_SCALE;
	return (distance(pixel, player_pos) < (double) MAP_SCALE / 170);
}

void	draw_map(t_cb *cb)
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
			if (x / MAP_SCALE < cb->map.width && y / MAP_SCALE < cb->map.height)
			{
				if (is_player(x, y, cb->player_pos))
					put_pixel(cb->img, x, y, 0xff0000);
				else if (cb->map.arr[y / MAP_SCALE][x / MAP_SCALE] == 1)
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
