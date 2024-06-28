/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:35:49 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 15:37:27 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_cb *cb)
{
	// if (cb->map)
	// free_map(cb->map);
	if (cb->img.img)
		mlx_destroy_image(cb->mlx, cb->img.img);
	if (cb->win)
		mlx_destroy_window(cb->mlx, cb->win);
	if (cb->mlx)
		mlx_destroy_display(cb->mlx);
	free(cb->mlx);
	free(cb->keybinds);
	exit(0);
	return (0);
}

int	on_loop(t_cb *cb)
{
	(void)cb;
	apply_all_keys(cb);
	printf("player_pos: %f, %f\n", cb->player_pos.x, cb->player_pos.y);
	ft_bzero(cb->img.addr, HEIGHT * cb->img.line_length);
    int map[10][10] =  {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
                        {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    draw_map(cb, map, 10, 10);
	return (0);
}

int	on_keypressed(int keycode, t_cb *cb)
{
	if (keycode == XK_Escape)
		return (close_win(cb));
	else
		set_key(keycode, 1, cb);
	return (0);
}

int	on_keyreleased(int keycode, t_cb *cb)
{
	set_key(keycode, 0, cb);
	return (0);
}

void	setup_hooks(t_cb *cb)
{
	mlx_hook(cb->win, 17, ButtonPressMask, close_win, cb);
	mlx_hook(cb->win, 2, KeyPressMask, on_keypressed, cb);
	mlx_hook(cb->win, 3, KeyReleaseMask, on_keyreleased, cb);
	mlx_loop_hook(cb->mlx, on_loop, cb);
}
