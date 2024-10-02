/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:35:49 by hrother           #+#    #+#             */
/*   Updated: 2024/10/02 10:48:04 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(t_cb *cb)
{
	exit_cub(cb, "window closed\n");
	exit(0);
	return (0);
}

void	set_deltatime(t_cb *cb)
{
	long		new_time;
	static long	old_time = 0;

	new_time = get_time_ms();
	cb->deltatime = (new_time - old_time) / 1000.0;
	// printf("fps: %f\n", 1 / cb->deltatime);
	old_time = new_time;
}

int	on_loop(t_cb *cb)
{
	set_deltatime(cb);
	cb->player.input = (t_vec2){0, 0};
	apply_all_keys(cb);
	cb->player.rot = clamp_rot(cb->player.rot);
	player_walk(cb);
	ft_bzero(cb->img.addr, HEIGHT * cb->img.line_length);
	draw_view(cb);
	mlx_put_image_to_window(cb->mlx, cb->win, cb->img.img, 0, 0);
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
