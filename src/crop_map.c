/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crop_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:42:12 by hrother           #+#    #+#             */
/*   Updated: 2024/10/06 17:42:25 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	copy_new_map(t_parser *parser, int limit[4])
{
	int	y;
	int	x;
	int	**new_arr;

	y = 0;
	x = 0;
	new_arr = ft_calloc(parser->cb->map.height, sizeof(int *));
	if (new_arr == NULL)
		exit_parser(parser, "malloc fail\n");
	while (y < parser->cb->map.height)
	{
		new_arr[y] = ft_calloc(parser->cb->map.width, sizeof(int));
		if (new_arr[y] == NULL)
			(free_ptr_arr((void **)new_arr, y), exit_parser(parser,
					"malloc fail\n"));
		x = 0;
		while (x < parser->cb->map.width && parser->cb->map.arr[y + limit[1]][x
			+ limit[0]] != -1)
		{
			new_arr[y][x] = parser->cb->map.arr[y + limit[1]][x + limit[0]];
			x++;
		}
		while (x < parser->cb->map.width)
			new_arr[y][x++] = 1;
		y++;
	}
	free_ptr_arr((void **)parser->cb->map.arr, parser->cb->map.y);
	parser->cb->map.y = 0;
	parser->cb->map.arr = new_arr;
}

void	crop_map(t_parser *parser)
{
	int	limit[4];

	limit[0] = 1000000;
	limit[1] = 1000000;
	limit[2] = 0;
	limit[3] = 0;
	get_limits(parser->cb->map, limit);
	parser->cb->map.width = limit[2] - limit[0] + 1;
	parser->cb->map.height = limit[3] - limit[1] + 1;
	copy_new_map(parser, limit);
	parser->cb->player.pos.x -= limit[0];
	parser->cb->player.pos.y -= limit[1];
}
