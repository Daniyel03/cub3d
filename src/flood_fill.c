/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:35 by hrother           #+#    #+#             */
/*   Updated: 2024/10/09 17:30:53 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

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

int	check_x(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i <= x)
	{
		if (map->arr[y][i] == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	fill_rec(t_parser *parser, int x, int y, int depth)
{
	int	ret;

	if (depth > MAX_DEPTH)
		exit_parser(parser, "your shit machine can handle this map\n");
	ret = SUCCESS;
	if (y < 0 || y > parser->cb->map.y - 1 || x < 0 || check_x(&parser->cb->map,
			x, y))
		return (FAILURE);
	if (parser->cb->map.arr[y][x] == 1 || parser->cb->map.arr[y][x] == 3)
		return (SUCCESS);
	if (parser->cb->map.arr[y][x] != 0)
		return (FAILURE);
	parser->cb->map.arr[y][x] = 3;
	ret |= fill_rec(parser, x - 1, y, depth + 1);
	ret |= fill_rec(parser, x + 1, y, depth + 1);
	ret |= fill_rec(parser, x, y - 1, depth + 1);
	ret |= fill_rec(parser, x, y + 1, depth + 1);
	return (ret);
}

void	setup_coord_lst(t_parser *parser)
{
	int	y;
	int	x;

	y = 0;
	while (y < parser->cb->map.height)
	{
		x = 0;
		while (x < parser->cb->map.width)
		{
			if (parser->cb->map.arr[y][x] == 3)
				append_cord(parser, x, y);
			x++;
		}
		y++;
	}
}

int	flood_fill(t_parser *parser)
{
	int	res;

	res = fill_rec(parser, (int)parser->cb->player.pos.x,
			(int)parser->cb->player.pos.y, 0);
	if (res == FAILURE)
		return (res);
	crop_map(parser);
	setup_coord_lst(parser);
	return (res);
}
