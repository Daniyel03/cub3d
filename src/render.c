/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/04 15:57:25 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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

void	check_x(t_cb *cb, t_vec2 *coor)
{
	double			highest_x;
	t_valid_cords	*temp;

	temp = cb->cords;
	highest_x = 0;
	while (temp)
	{
		if (temp->y == floor((*coor).y) && highest_x < floor(temp->x))
			highest_x = floor(temp->x);
		temp = temp->next;
	}
	// printf("highest %f in %f\n", x, (*coor).y);
	if (highest_x + 1 < floor((*coor).x))
	{
		(*coor).x = highest_x + 1;
	}
	// if (x < floor((*coor).x))
	// printf("invalid %f in %f\n", (*coor).x, (*coor).y);
}

int	invalid_x(t_vec2 vec, t_cb *cb)
{
	t_valid_cords	*temp;

	temp = cb->cords;
	while (temp)
	{
		if (floor(vec.y) == temp->y && (vec.x >= temp->x && vec.x <= temp->x
				+ 1))
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (1);
	// return (printf("x %f y%f\n", vec.x, vec.y), 1);
	return (0);
}

int	check_is_wall(t_cb *cb, t_vec2 coor, t_vec2 direction)
{
	// TODO: this is a haky fix. Maybe find sth cleaner
	coor = add_vec(coor, scale_vec(direction, 0.0000001));
	// printf("%f %f\n", coor.x, coor.y);
	// if (coor.x > 1.1)
	// 	coor.x = floor(coor.x * 10) / 10;
	// if (coor.y > 1.1)
	// 	coor.y = floor(coor.y * 10) / 10;
	check_x(cb, &coor);
	// (void)cb;
	if (coor.y < 0)
	{
		return (1);
	}
	if (coor.x < 0 || invalid_x(coor, cb))
	{
		return (1);
	}
	if (coor.y > cb->map.y)
	{
		return (1);
	}
	if (cb->map.arr[(int)coor.y][(int)coor.x] != 3)
	{
		return (1);
	}
	return (0);
}

t_vec2	next_wall_x(t_cb *cb, t_vec2 dir)
{
	double	scale;
	t_vec2	wall;

	if (dir.x > 0)
		scale = (ceil(cb->player.pos.x) - cb->player.pos.x) / dir.x;
	else if (dir.x < 0)
		scale = (floor(cb->player.pos.x) - cb->player.pos.x) / dir.x;
	else
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, scale);
	wall = add_vec(cb->player.pos, dir);
	if (dir.x == 0.0)
		return ((t_vec2){0, 0});
	dir = scale_vec(dir, 1 / fabs(dir.x));
	while (!check_is_wall(cb, wall, dir))
	{
		wall = add_vec(wall, dir);
	}
	return (wall);
}

t_vec2	next_wall_y(t_cb *cb, t_vec2 dir)
{
	double	scale;
	t_vec2	wall;

	if (dir.y > 0.0001)
		scale = (ceil(cb->player.pos.y) - cb->player.pos.y) / dir.y;
	else if (dir.y < -0.0001)
		scale = (floor(cb->player.pos.y) - cb->player.pos.y) / dir.y;
	else
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, scale);
	wall = add_vec(cb->player.pos, dir);
	if (dir.y < 0.001 && dir.y > -0.001)
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, 1 / fabs(dir.y));
	while (!check_is_wall(cb, wall, dir))
	{
		wall = add_vec(wall, dir);
	}
	return (wall);
}

t_vec2	next_wall(t_render_data *data, t_vec2 dir)
{
	t_vec2	wall_x;
	t_vec2	wall_y;

	wall_x = next_wall_x(data->cb, dir);
	wall_y = next_wall_y(data->cb, dir);
	if (distance(data->cb->player.pos, wall_x) < distance(data->cb->player.pos,
			wall_y))
	{
		if (dir.x > 0)
			data->texture = data->cb->map.textures[1];
		else
			data->texture = data->cb->map.textures[3];
		return (wall_x);
	}
	else
	{
		if (dir.y > 0)
			data->texture = data->cb->map.textures[2];
		else
			data->texture = data->cb->map.textures[0];
		return (wall_y);
	}
}

/*
void	draw_player_rays(t_cb *cb)
{
	t_vec2	vec;
	int		i;
	double	rot_offset;

	i = 0;
	while (i < WIDTH)
	{
		rot_offset = FOV / WIDTH * i - FOV / 2;
		vec = get_dir_vec(1, cb->player.rot + rot_offset);
		vec = next_wall(cb, vec);
		draw_line(scale_vec(cb->player.pos, MAP_SCALE), scale_vec(vec,
				MAP_SCALE), WHITE, cb->img);
		i++;
	}
}
*/

double	angle(t_vec2 a, t_vec2 b)
{
	double	dot;
	double	mag1;
	double	mag2;

	dot = a.x * b.x + a.y * b.y;
	mag1 = sqrt(a.x * a.x + a.y * a.y);
	mag2 = sqrt(b.x * b.x + b.y * b.y);
	return (acos(dot / (mag1 * mag2)));
}

void	draw_view(t_cb *cb)
{
	t_vec2			vec;
	t_render_data	data;
	double			plane_len;
	double			offset_vec;

	data.cb = cb;
	data.col = 0;
	plane_len = 2 * tan(FOV / 2);
	while (data.col < WIDTH)
	{
		offset_vec = plane_len / 2 - plane_len / WIDTH * data.col;
		vec = get_dir_vec(1, cb->player.rot);
		vec.x += vec.y * offset_vec;
		vec.y += -vec.x * offset_vec;
		data.rot_offset = angle(get_dir_vec(1, cb->player.rot), vec);
		data.wall_hit = next_wall(&data, vec);
		draw_wall_line(&data);
		data.col++;
	}
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
	// draw_player_rays(cb);
}
