/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:16:21 by hrother           #+#    #+#             */
/*   Updated: 2024/10/04 22:58:28 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	get_pixel(t_img img, int x, int y)
{
	char	*dst;

	if (y >= img.height || x >= img.width || y < 0 || x < 0)
		return (-1);
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_line(t_render_data *data)
{
	int		i;
	double	y_scale;
	int		y_offest;

	y_scale = (double)data->texture.height / data->wall_height;
	y_offest = HEIGHT / 2 - data->wall_height / 2 + (data->cb->player.z_pos
			* data->wall_height / 10);
	i = 0;
	while (i < y_offest && i < HEIGHT)
	{
		put_pixel(data->cb->img, data->cam_col, i, data->cb->map.ceil_color);
		i++;
	}
	while (i < y_offest + data->wall_height && i < HEIGHT)
	{
		put_pixel(data->cb->img, data->cam_col, i, get_pixel(data->texture,
				data->texture_col, (i - y_offest) * y_scale));
		i++;
	}
	while (i < HEIGHT)
	{
		put_pixel(data->cb->img, data->cam_col, i, data->cb->map.floor_color);
		i++;
	}
}
