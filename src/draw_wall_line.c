/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:16:21 by hrother           #+#    #+#             */
/*   Updated: 2024/09/30 12:16:23 by hrother          ###   ########.fr       */
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
	int		len;
	int		i;
	double	y_scale;
	int		y_offest;

 	len = HEIGHT / (distance(data->cb->player.pos, data->wall_hit)
			* (data->rot_offset));
	y_scale = (double)data->texture.height / len;
	y_offest = HEIGHT / 2 - len / 2;
	i = 0;
	while (i < y_offest && i < HEIGHT)
	{
		put_pixel(data->cb->img, data->cam_col, i, data->cb->map.ceil_color);
		i++;
	}
	while (i < y_offest + len && i < HEIGHT)
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
