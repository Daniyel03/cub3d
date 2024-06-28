/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:16 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 15:02:00 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_to_val(int *val, int rate)
{
	*val += rate;
}

void	init_keybind(t_keybind *keybind, int keycode, t_key_func func, int *val,
		int rate)
{
	keybind->keycode = keycode;
	keybind->pressed = 0;
	keybind->val = val;
	keybind->rate = rate;
	keybind->func = func;
}

void	init_keybinds(t_cb *cb)
{
	cb->keybinds = malloc(sizeof(t_keybind) * 5);
	init_keybind(&cb->keybinds[0], XK_w, add_to_val, &cb->player_pos.y, 1);
    init_keybind(&cb->keybinds[1], XK_s, add_to_val, &cb->player_pos.y, -1);
    init_keybind(&cb->keybinds[2], XK_a, add_to_val, &cb->player_pos.x, -1);
    init_keybind(&cb->keybinds[3], XK_d, add_to_val, &cb->player_pos.x, 1);
	init_keybind(&cb->keybinds[4], 0, NULL, NULL, 0);
}

int	set_key(int keycode, int state, t_cb *cb)
{
	int	i;

	i = 0;
	while (cb->keybinds[i].keycode != 0)
	{
		if (cb->keybinds[i].keycode == keycode)
		{
			printf("set key: %d to %d\n", keycode, state);
			cb->keybinds[i].pressed = state;
			return (0);
		}
		i++;
	}
	return (1);
}

void apply_all_keys(t_cb *cb)
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

