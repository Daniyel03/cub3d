/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:16 by hrother           #+#    #+#             */
/*   Updated: 2024/06/30 18:29:08 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	add_to_val(void *val, double rate)
{
	*((double *)val) += rate;
}

void	set_to(void *val, double rate)
{
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
	cb->keybinds = malloc(sizeof(t_keybind) * 7);
	init_keybind(&cb->keybinds[0], XK_s, set_to, &cb->player.input.y, -0.07);
	init_keybind(&cb->keybinds[1], XK_w, set_to, &cb->player.input.y, 0.07);
	init_keybind(&cb->keybinds[2], XK_a, set_to, &cb->player.input.x, 0.07);
	init_keybind(&cb->keybinds[3], XK_d, set_to, &cb->player.input.x, -0.07);
	init_keybind(&cb->keybinds[4], XK_Left, add_to_val, &cb->player.rot, 0.05);
	init_keybind(&cb->keybinds[5], XK_Right, add_to_val, &cb->player.rot,
		-0.05);
	init_keybind(&cb->keybinds[6], 0, NULL, NULL, 0);
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
			cb->keybinds[i].func(cb->keybinds[i].val, cb->keybinds[i].rate);
		i++;
	}
}
