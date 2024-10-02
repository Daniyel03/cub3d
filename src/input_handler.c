/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:16 by hrother           #+#    #+#             */
/*   Updated: 2024/10/02 14:13:35 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	add_to_val(void *val, double rate, t_cb *cb)
{
	*((double *)val) += rate * cb->deltatime;
}

void	set_to(void *val, double rate, t_cb *cb)
{
	(void)cb;
	printf("setting to: %f\n", rate);
	*((double *)val) = rate;
}

void	init_keybind(t_keybind *keybind, int keycode, t_key_func func,
		double *val, double rate)
{
	keybind->keycode = keycode;
	keybind->pressed = 0;
	keybind->val = val;
	keybind->rate = rate;
	keybind->func = func;
}

void	init_keybinds(t_cb *cb)
{
	cb->keybinds = malloc(sizeof(t_keybind) * 10);
	init_keybind(&cb->keybinds[0], XK_s, add_to_val, &cb->player.input.y,
		-WALK_SPEED);
	init_keybind(&cb->keybinds[1], XK_w, add_to_val, &cb->player.input.y,
		WALK_SPEED);
	init_keybind(&cb->keybinds[2], XK_a, add_to_val, &cb->player.input.x,
		WALK_SPEED);
	init_keybind(&cb->keybinds[3], XK_d, add_to_val, &cb->player.input.x,
		-WALK_SPEED);
	init_keybind(&cb->keybinds[4], XK_Left, add_to_val, &cb->player.rot,
		TURN_SPEED);
	init_keybind(&cb->keybinds[5], XK_Right, add_to_val, &cb->player.rot,
		-TURN_SPEED);
	init_keybind(&cb->keybinds[6], XK_space, set_to, &cb->player.up_vel,
		JUMP_FORCE);
	init_keybind(&cb->keybinds[7], 0, NULL, NULL, 0);
}

int	set_key(int keycode, int state, t_cb *cb)
{
	int	i;

	i = 0;
	while (cb->keybinds[i].keycode != 0)
	{
		if (cb->keybinds[i].keycode == keycode)
		{
			cb->keybinds[i].pressed = state;
			return (0);
		}
		i++;
	}
	return (1);
}

void	apply_all_keys(t_cb *cb)
{
	int	i;

	i = 0;
	while (cb->keybinds[i].keycode != 0)
	{
		if (cb->keybinds[i].pressed)
			cb->keybinds[i].func(cb->keybinds[i].val, cb->keybinds[i].rate, cb);
		i++;
	}
}
