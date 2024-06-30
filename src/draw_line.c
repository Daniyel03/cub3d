/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:57:55 by hannes            #+#    #+#             */
/*   Updated: 2024/01/05 23:54:47 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line_data	set_line_data(t_vec2 start, t_vec2 end)
{
	t_line_data	data;
	int			temp;

	data.dx = end.x - start.x;
	data.dy = end.y - start.y;
	data.step_x = 1;
	if (data.dx < 0)
		data.step_x = -1;
	data.step_y = 1;
	if (data.dy < 0)
		data.step_y = -1;
	data.dx = abs(data.dx);
	data.dy = abs(data.dy);
	data.swap = 0;
	if (data.dy > data.dx)
	{
		data.swap = 1;
		temp = data.dx;
		data.dx = data.dy;
		data.dy = temp;
	}
	data.x = start.x;
	data.y = start.y;
	data.error = 2 * data.dy - data.dx;
	return (data);
}

void	draw_line(t_vec2 start, t_vec2 end, t_img img)
{
	t_line_data	data;
	int			i;

	data = set_line_data(start, end);
	i = 0;
	while (i <= data.dx)
	{
		put_pixel(img, (int)data.x, (int)data.y, WHITE);
		if (data.error > 0)
		{
			if (data.swap)
				data.x += data.step_x;
			else
				data.y += data.step_y;
			data.error -= 2 * data.dx;
		}
		if (data.swap)
			data.y += data.step_y;
		else
			data.x += data.step_x;
		data.error += 2 * data.dy;
		i++;
	}
}
