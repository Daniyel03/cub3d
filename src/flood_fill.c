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
