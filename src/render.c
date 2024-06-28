/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:15:28 by hannes            #+#    #+#             */
/*   Updated: 2024/06/28 11:04:38 by dscholz          ###   ########.fr       */
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
			if (x / 30 < x_max && y / 30 < y_max)
			{
				if (map[y / 30][x / 30] == 1)
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
