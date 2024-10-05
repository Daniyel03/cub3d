/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:41:07 by hrother           #+#    #+#             */
/*   Updated: 2024/10/05 14:32:52 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	is_wall(t_cb *cb, int x, int y)
{

	return (x < 0 || y < 0 || x >= cb->map.width || y >= cb->map.height || cb->map.arr[y][x] != 3);
	/*
	t_valid_cords	*temp;
	temp = cb->cords;
	while (temp)
	{
		if (temp->x == x && temp->y == y)
			return (0);
		temp = temp->next;
	}
	return (1);
	*/
}

int	check_hit_wall(t_cb *cb, t_vec2 coor, t_vec2 direction)
{
	coor = add_vec(coor, scale_vec(direction, 0.0000001));
	(void)direction;
	return (is_wall(cb, (int) floor(coor.x), (int) floor(coor.y)));
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
	while (!check_hit_wall(cb, wall, dir))
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
	while (!check_hit_wall(cb, wall, dir))
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
			data->texture = data->cb->map.textures[3];
		else
			data->texture = data->cb->map.textures[1];
		data->texture_col = (wall_x.y - floor(wall_x.y)) * data->texture.width;
		return (wall_x);
	}
	else
	{
		if (dir.y > 0)
			data->texture = data->cb->map.textures[0];
		else
			data->texture = data->cb->map.textures[2];
		data->texture_col = (wall_y.x - floor(wall_y.x)) * data->texture.width;
		return (wall_y);
	}
}
