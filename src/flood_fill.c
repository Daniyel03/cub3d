/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:35 by hrother           #+#    #+#             */
/*   Updated: 2024/06/29 11:24:16 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_rec(t_map *map, int x, int y)
{
	int	ret;

	ret = SUCCESS;
	if (map->arr[y][x] == 1 || map->arr[y][x] == 3)
		return (SUCCESS);
	if (y <= 0 || y >= map->height - 1 || x <= 0 || x >= map->width - 1)
		return (FAILURE);
	if (map->arr[y][x] != 0)
		return (FAILURE);
	map->arr[y][x] = 3;
	ret |= fill_rec(map, x - 1, y);
	ret |= fill_rec(map, x + 1, y);
	ret |= fill_rec(map, x, y - 1);
	ret |= fill_rec(map, x, y + 1);
	return (ret);
}

int	flood_fill(t_cb *cb)
{
	return (fill_rec(&cb->map, (int)cb->player_pos.x, (int)cb->player_pos.y));
}

void	print_map(t_map map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			printf("%d ", map.arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	**malloc_example_map(int arr[10][10])
{
	int	i;
	int	**ret;

	i = 0;
	ret = malloc(10 * sizeof(int *));
	while (i < 10)
	{
		ret[i] = malloc(10 * sizeof(int));
		ft_memcpy(ret[i], arr[i], 10 * sizeof(int));
		i++;
	}
	return (ret);
}

/*
int	main(void)
{
	int		arr[10][10] =  {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                            {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
                            {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
                            {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                            {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	t_cb	cb;

	cb.map = (t_map){0, malloc_example_map(arr), 10, 10};
	cb.player_pos.x = 2;
	cb.player_pos.y = 2;
	print_map(cb.map);
	printf ("valid: %d\n", flood_fill(&cb));
	print_map(cb.map);
}
*/
