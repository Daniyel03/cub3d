/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:35:49 by hrother           #+#    #+#             */
/*   Updated: 2024/10/05 12:01:59 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(t_cb *cb)
{
	exit_cub(cb, NULL, 0);
	return (0);
}

int	on_loop(t_cb *cb)
{
	set_deltatime(cb);
	cb->player.input = (t_vec2){0, 0};
	apply_all_keys(cb);
	cb->player.rot = clamp_rot(cb->player.rot);
	player_walk(cb);
	if (cb->player.z_pos > 0)
		cb->player.up_vel -= GRAVITY * cb->deltatime;
	else if (cb->player.up_vel < 0)
		cb->player.up_vel = 0;
	cb->player.z_pos += cb->player.up_vel * cb->deltatime;
	ft_bzero(cb->img.addr, HEIGHT * cb->img.line_length);
	draw_view(cb);
	if (cb->show_map)
		draw_map(cb);
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

int	on_mouse_move(int x, int y, t_cb *cb)
{
	(void)y;
	int delta_x = x - (WIDTH/2);
	cb->player.rot -= delta_x * SENSITIVITY * 0.001;
	printf("mouse x:%i\n", delta_x);
	mlx_mouse_move(cb->mlx, cb->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

void	setup_hooks(t_cb *cb)
{
	mlx_hook(cb->win, 17, ButtonPressMask, close_win, cb);
	mlx_hook(cb->win, 2, KeyPressMask, on_keypressed, cb);
	mlx_hook(cb->win, 3, KeyReleaseMask, on_keyreleased, cb);
	mlx_hook(cb->win, MotionNotify, PointerMotionMask, on_mouse_move, cb);
	mlx_loop_hook(cb->mlx, on_loop, cb);
}
