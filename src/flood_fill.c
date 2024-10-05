/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:35 by hrother           #+#    #+#             */
/*   Updated: 2024/09/30 12:22:31 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "parser.h"

void	print_cord(t_cb *cb)
{
	t_valid_cords	*temp;

	temp = cb->cords;
	while (temp)
	{
		printf("x '%d' y '%d'\n", temp->x, temp->y);
		temp = temp->next;
	}
}

void	append_cord(t_parser *parser, int x, int y)
{
	t_valid_cords	*temp;

	temp = parser->cb->cords;
	if (!temp)
	{
		parser->cb->cords = malloc(sizeof(t_valid_cords));
		temp = parser->cb->cords;
		if (temp == NULL)
			exit_parser(parser, "malloc fail\n");
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_valid_cords));
		if (temp->next == NULL)
			exit_parser(parser, "malloc fail\n");
		temp = temp->next;
	}
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
}

int	fill_rec(t_parser *parser, t_map *map, int x, int y)
{
	int	ret;

	ret = SUCCESS;
	if (y < 0 || y > map->y - 1 || x < 0)
		return (FAILURE);
	if (map->arr[y][x] == 1 || map->arr[y][x] == 3)
		return (SUCCESS);
	if (map->arr[y][x] != 0)
		return (FAILURE);
	map->arr[y][x] = 3;
	append_cord(parser, x, y);
	ret |= fill_rec(parser, map, x - 1, y);
	ret |= fill_rec(parser, map, x + 1, y);
	ret |= fill_rec(parser, map, x, y - 1);
	ret |= fill_rec(parser, map, x, y + 1);
	return (ret);
}

void	get_limits(t_map map, int limit[])
{
	int	y;
	int	x;

	y = 0;
	while (y < map.y)
	{
		x = 0;
		while (map.arr[y][x] != -1)
		{
			if (map.arr[y][x] == 3)
			{
				if (x < limit[0])
					limit[0] = x;
				if (y < limit[1])
					limit[1] = y;
				if (x > limit[2])
					limit[2] = x;
				if (y > limit[3])
					limit[3] = y;
			}
			x++;
		}
		y++;
	}
}

void	copy_new_map(t_map *map, int limit[4])
{
	int	y;
	int	x;
	int	**new_arr;

	y = 0;
	x = 0;
	new_arr = ft_calloc(map->height, sizeof(int *));
	while (y < map->height)
	{
		new_arr[y] = ft_calloc(map->width, sizeof(int));
		x = 0;
		while (x < map->width && map->arr[y + limit[1]][x + limit[0]] != -1)
		{
			new_arr[y][x] = map->arr[y + limit[1]][x + limit[0]];
			x++;
		}
		while (x < map->width)
			new_arr[y][x++] = 1;
		y++;
	}
	free(map->arr);
	map->arr = new_arr;
}

void	crop_map(t_parser *parser)
{
	int	limit[4] = {1000, 1000, 0, 0};

	get_limits(parser->cb->map, limit);
	printf("%i,%i; %i,%i\n", limit[0], limit[1], limit[2], limit[3]);
	parser->cb->map.width = limit[2] - limit[0] + 1;
	parser->cb->map.height = limit[3] - limit[1] + 1;
	copy_new_map(&parser->cb->map, limit);
}

int	flood_fill(t_parser *parser)
{
	int	res;

	res = fill_rec(parser, &parser->cb->map, (int)parser->cb->player.pos.x,
			(int)parser->cb->player.pos.y);
	crop_map(parser);
	return (res);
}
