/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:00:00 by dscholz           #+#    #+#             */
/*   Updated: 2024/09/30 12:18:24 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	angle(t_vec2 a, t_vec2 b)
{
	double	dot;
	double	mag1;
	double	mag2;

	dot = a.x * b.x + a.y * b.y;
	mag1 = sqrt(a.x * a.x + a.y * a.y);
	mag2 = sqrt(b.x * b.x + b.y * b.y);
	return ((dot / (mag1 * mag2)));
}

void	draw_view(t_cb *cb)
{
	t_vec2			player_dir;
	t_render_data	data;
	double			plane_len;
	double			offset_vec;

	data.cb = cb;
	data.cam_col = 0;
	plane_len = 2 * tan(FOV / 2);
	while (data.cam_col < WIDTH)
	{
		offset_vec = plane_len / 2 - plane_len / WIDTH * data.cam_col;
		player_dir = get_dir_vec(1, cb->player.rot);
		data.ray_dir.x = player_dir.x + player_dir.y * offset_vec;
		data.ray_dir.y = player_dir.y - player_dir.x * offset_vec;
		data.wall_hit = next_wall(&data, data.ray_dir);
		data.rot_offset = angle(get_dir_vec(1, cb->player.rot), data.ray_dir);
		data.wall_height = HEIGHT / (distance(data.cb->player.pos,
					data.wall_hit) * (data.rot_offset));
		draw_wall_line(&data);
		data.cam_col++;
	}
}
