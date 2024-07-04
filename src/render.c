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


void	check_x(t_cb *cb, t_vec2 *coor)
{
	double highest_x;
	t_valid_cords *temp = cb->cords;
	highest_x = 0;
	while (temp)
	{
		if (temp->y == floor((*coor).y) && highest_x < floor(temp->x))
			highest_x = floor(temp->x);
		temp = temp->next;
	}
	// printf("highest %f in %f\n", x, (*coor).y);
	if (highest_x + 1 < floor((*coor).x))
		(*coor).x = highest_x + 1;
	// if (x < floor((*coor).x))
		// printf("invalid %f in %f\n", (*coor).x, (*coor).y);
	
}

int	check_is_wall(t_cb *cb, t_map map, t_vec2 coor, t_vec2 direction)
{
	coor = add_vec(coor, scale_vec(direction, 0.00001));
	// printf("%f %f\n", coor.x, coor.y);
	// if (coor.x > 1.1)
	// 	coor.x = floor(coor.x * 10) / 10;
	// if (coor.y > 1.1)
	// 	coor.y = floor(coor.y * 10) / 10;
	check_x(cb, &coor);
	// (void)cb;
	if (coor.y < 0) {
		return 1;
	}
	if (coor.x < 0) {
		return 1;
	}
	if (coor.y > map.y) {
		return 1;
	}
	if (map.arr[(int)coor.y][(int)coor.x] != 3) {
		return 1;
	}

	return 0;
}

t_vec2	next_wall_x(t_cb *cb, t_vec2 pos, t_vec2 dir, t_map map)
{
	double	scale;
	t_vec2	wall;

	if (dir.x > 0)
		scale = (ceil(pos.x) - pos.x) / dir.x;
	else if (dir.x < 0)
		scale = (floor(pos.x) - pos.x) / dir.x;
	else
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, scale);
	wall = add_vec(pos, dir);
	if (dir.x == 0.0)
		return ((t_vec2){0, 0});
	dir = scale_vec(dir, 1 / fabs(dir.x));
	while (!check_is_wall(cb, map, wall, dir))
	{
		wall = add_vec(wall, dir);
	}
	return (wall);
}

t_vec2	next_wall_y(t_cb *cb, t_vec2 pos, t_vec2 dir, t_map map)
{
	double	scale;
	t_vec2	wall;

	if (dir.y > 0.0001)
		scale = (ceil(pos.y) - pos.y) / dir.y;
	else if (dir.y < -0.0001)
		scale = (floor(pos.y) - pos.y) / dir.y;
	else
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, scale);
	wall = add_vec(pos, dir);
	if (dir.y < 0.001 && dir.y > -0.001)
		return ((t_vec2){-10000, -10000});
	dir = scale_vec(dir, 1 / fabs(dir.y));
	while (!check_is_wall(cb, map, wall, dir))
	{
		wall = add_vec(wall, dir);
	}
	return (wall);
}

t_vec2	next_wall(t_cb *cb, t_vec2 pos, t_vec2 dir, t_map map)
{
	t_vec2	wall_x;
	t_vec2	wall_y;

	wall_x = next_wall_x(cb, pos, dir, map);
	wall_y = next_wall_y(cb, pos, dir, map);
	if (distance(pos, wall_x) < distance(pos, wall_y))
		return (wall_x);
	else
		return (wall_y);
}

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
		vec = next_wall(cb, cb->player.pos, vec, cb->map);
		draw_line(scale_vec(cb->player.pos, MAP_SCALE), scale_vec(vec,
				MAP_SCALE), WHITE, cb->img);
		i++;
	}
}

void	draw_view(t_cb *cb)
{
	t_vec2	vec;
	int		i;
	double	rot_offset;

	i = 0;
	while (i < WIDTH)
	{
		rot_offset = FOV / 2 - FOV / WIDTH * i;
		vec = get_dir_vec(1, cb->player.rot + rot_offset);
		vec = next_wall(cb, cb->player.pos, vec, cb->map);
		draw_wall_line(i, vec, cb);
		i++;
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
	draw_player_rays(cb);
}
