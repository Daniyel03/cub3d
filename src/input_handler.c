/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:16 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 14:29:36 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void add_to_val(int *val, int rate)
{
    *val += rate;
}

t_keybind init_keybind(int keycode, t_key_func func, int *val, int rate)
{
    t_keybind keybind;

    keybind.keycode = keycode;
    keybind.pressed = 0;
    keybind.val = val;
    keybind.rate = rate;
    keybind.func = func;
    return (keybind);
}

void init_keybinds(t_cb cb)
{
    cb.keybinds = malloc(sizeof(t_keybind) * 4);
    cb.keybinds[0] = init_keybind(XK_w, add_to_val, &cb.player_pos.y, 1);
    cb.keybinds[1] = init_keybind(XK_s, add_to_val, &cb.player_pos.y, -1);
    cb.keybinds[2] = init_keybind(XK_a, add_to_val, &cb.player_pos.x, -1);
    cb.keybinds[3] = init_keybind(XK_d, add_to_val, &cb.player_pos.x, 1);
}
