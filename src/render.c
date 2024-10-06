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
		data.wall_height = WIDTH / plane_len / (distance(data.cb->player.pos,
					data.wall_hit) * (data.rot_offset));
		draw_wall_line(&data);
		data.cam_col++;
	}
}

void	draw_player_rays(t_cb *cb)
{
	t_vec2			vec;
	int				i;
	double			rot_offset;
	t_render_data	data;

	data.cb = cb;
	i = 0;
	while (i < WIDTH)
	{
		rot_offset = FOV / WIDTH * i - FOV / 2;
		vec = get_dir_vec(1, cb->player.rot + rot_offset);
		vec = next_wall(&data, vec);
		draw_line(add_vec(scale_vec(cb->player.pos, MAP_SCALE), (t_vec2){MAP_X,
				MAP_Y}), add_vec(scale_vec(vec, MAP_SCALE), (t_vec2){MAP_X,
				MAP_Y}), WHITE, cb->img);
		i += 100;
	}
}
int	is_player(int x, int y, t_vec2 player_pos, double scale)
{
	t_vec2	pixel;

	pixel.x = (double)x / scale;
	pixel.y = (double)y / scale;
	return (distance(pixel, player_pos) < 0.3);
}

void	draw_map(t_cb *cb)
{
	int	y;
	int	x;

	double scale = MAP_SCALE / (double) cb->map.width;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y / scale >= cb->map.height || x / scale > cb->map.width)
				break ;
			if (is_player(x, y, cb->player.pos, scale))
				put_pixel(cb->img, x + MAP_X, y + MAP_Y, 0xff0000);
			else if (cb->map.arr[(int)(y / scale)][(int)(x / scale)] == 3)
				put_pixel(cb->img, x + MAP_X, y + MAP_Y, 0x222222);
			x++;
		}
		y++;
	}
	// draw_player_rays(cb);
}
