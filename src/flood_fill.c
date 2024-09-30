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

void	append_cord(t_cb *cb, int x, int y)
{
	t_valid_cords	*temp;

	temp = cb->cords;
	if (!temp)
	{
		cb->cords = malloc(sizeof(t_valid_cords));
		temp = cb->cords;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_valid_cords));
		temp = temp->next;
	}
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
}

int	fill_rec(t_cb *cb, t_map *map, int x, int y)
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
	append_cord(cb, x, y);
	ret |= fill_rec(cb, map, x - 1, y);
	ret |= fill_rec(cb, map, x + 1, y);
	ret |= fill_rec(cb, map, x, y - 1);
	ret |= fill_rec(cb, map, x, y + 1);
	return (ret);
}

int	flood_fill(t_cb *cb)
{
	return (fill_rec(cb, &cb->map, (int)cb->player.pos.x,
			(int)cb->player.pos.y));
}

/*
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

int	main(void)
{
	t_cb	cb;

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
	cb.map = (t_map){0, malloc_example_map(arr), 10, 10};
	cb.player.pos.x = 2;
	cb.player.pos.y = 2;
	print_map(cb.map);
	printf ("valid: %d\n", flood_fill(&cb));
	print_map(cb.map);
}
*/
