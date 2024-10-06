/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:27:52 by hrother           #+#    #+#             */
/*   Updated: 2024/10/06 16:15:10 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <X11/X.h>

int	check_if_diagonal_and_wall(t_cb *cb, t_vec2 pos, t_vec2 input)
{
	if ((floor(pos.x) - floor(pos.x + input.x)) && ((floor(pos.y) - floor(pos.y
					+ input.y))) && is_wall(cb, floor(pos.x + input.x),
			floor(pos.y + input.y)))
		return (1);
	if ((input.y < 0 && input.x == 0) && (floor(pos.y) + 0.02) > (pos.y + input.y) && is_wall(cb, floor(pos.y + input.y - 0.02), floor(pos.x + input.x)))
		return 1;
	return (0);
}

void	adjust_if_pos_is_wall(t_cb *cb)
{
	if ((cb->player.pos.x + cb->player.input.x) == ceil(cb->player.pos.x)
		&& cb->player.input.x > 0)
		cb->player.input.x -= 0.02;
	else if ((cb->player.pos.x + cb->player.input.x) == floor(cb->player.pos.x)
		&& cb->player.input.x < 0)
		cb->player.input.x += 0.02;
	if ((cb->player.pos.y + cb->player.input.y) == ceil(cb->player.pos.y)
		&& cb->player.input.y > 0)
		cb->player.input.y -= 0.02;
	else if ((cb->player.pos.y + cb->player.input.y) == floor(cb->player.pos.y)
		&& cb->player.input.y < 0)
		cb->player.input.y += 0.02;
}

void	check_and_adjust_x_input(t_cb *cb)
{
	t_valid_cords	*temp;

	temp = cb->cords;
	while (temp)
	{
		if (((cb->player.pos.x + cb->player.input.x) > temp->x)
			&& (cb->player.pos.x + cb->player.input.x) < temp->x + 1
			&& (cb->player.pos.y >= temp->y && cb->player.pos.y <= temp->y + 1))
		{
			break ;
		}
		temp = temp->next;
		if (!temp)
		{
			if (cb->player.input.x < 0)
				cb->player.input.x = -1 * (cb->player.pos.x
						- floor(cb->player.pos.x));
			else
				cb->player.input.x = (ceil(cb->player.pos.x)
						- cb->player.pos.x);
		}
	}
	temp = cb->cords;
}

void	check_and_adjust_y_input(t_cb *cb)
{
	t_valid_cords	*temp;

	temp = cb->cords;
	while (temp)
	{
		if (((cb->player.pos.y + cb->player.input.y) > temp->y)
			&& (cb->player.pos.y + cb->player.input.y) < temp->y + 1
			&& (cb->player.pos.x >= temp->x && cb->player.pos.x <= temp->x + 1))
			break ;
		temp = temp->next;
		if (!temp)
		{
			if (cb->player.input.y < 0)
				cb->player.input.y = -1 * (cb->player.pos.y
						- floor(cb->player.pos.y));
			else
				cb->player.input.y = (ceil(cb->player.pos.y)
						- cb->player.pos.y);
		}
	}
}

void	player_walk(t_cb *cb)
{
	cb->player.input = rotate(cb->player.input, cb->player.rot * -1);
	check_and_adjust_x_input(cb);
	check_and_adjust_y_input(cb);
	adjust_if_pos_is_wall(cb);
	if (!check_if_diagonal_and_wall(cb, cb->player.pos, cb->player.input))
	{
		cb->player.pos.x += cb->player.input.x;
		cb->player.pos.y += cb->player.input.y;
	}
	printf("x %f y %f, x %f y %f\n", cb->player.pos.x, cb->player.pos.y, cb->player.input.x, cb->player.input.y);
}
