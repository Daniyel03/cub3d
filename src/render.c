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

	pixel.x = (double)x / MAP_SCALE;
	pixel.y = (double)y / MAP_SCALE;
	return (distance(pixel, player_pos) < (double)MAP_SCALE * 0.004);
}

int	check_is_wall(t_map map, t_vec2 coor, t_vec2 direction)
{
	coor = add_vec(coor, scale_vec(direction, 0.01));
	return (coor.y < 0 || coor.x < 0 || coor.y > map.y
		|| map.arr[(int)coor.y][(int)coor.x] != 3);
}

t_vec2	next_wall(t_vec2 pos, t_vec2 dir, t_map map)
{
	double	scale;
	t_vec2	wall;

	scale = 1;
	(void)map;
	if (dir.x > 0)
		scale = (ceil(pos.x) - pos.x) / dir.x;
	else if (dir.x < 0)
		scale = (floor(pos.x) - pos.x) / dir.x;
	dir = scale_vec(dir, scale);
	wall.x = pos.x + dir.x;
	wall.y = pos.y + dir.y;
	if (dir.x == 0.0)
		return ((t_vec2){0, 0});
	dir = scale_vec(dir, 1 / fabs(dir.x));
	printf("dir: %f, %f\n", dir.x, dir.y);
	while (!check_is_wall(map, wall, dir))
	{
		wall = add_vec(wall, dir);
	}
	return (wall);
}

void	draw_player_direction(t_cb *cb)
{
	t_vec2	direction;

	direction = get_dir_vec(1, cb->player.rot);
	direction = next_wall(cb->player.pos, direction, cb->map);
	draw_line(scale_vec(cb->player.pos, MAP_SCALE), scale_vec(direction,
			MAP_SCALE), cb->img);
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
			if (y / MAP_SCALE >= cb->map.y || cb->map.arr[y / MAP_SCALE][x
				/ MAP_SCALE] == -1)
				break ;
			if (is_player(x, y, cb->player.pos))
				put_pixel(cb->img, x, y, 0xff0000);
			else if (cb->map.arr[y / MAP_SCALE][x / MAP_SCALE] == 1)
				put_pixel(cb->img, x, y, 0x0000ff);
			else if (cb->map.arr[y / MAP_SCALE][x / MAP_SCALE] == 3)
				put_pixel(cb->img, x, y, 0x00ff00);
			x++;
		}
		y++;
	}
	draw_player_direction(cb);
}
