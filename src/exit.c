/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:47:19 by hannes            #+#    #+#             */
/*   Updated: 2024/10/05 14:33:01 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cb *cb)
{
	if (cb->map.arr)
	{
		if (cb->map.height)
			while (cb->map.height)
				free(cb->map.arr[--cb->map.height]);
		free(cb->map.arr);
	}
	if (cb->map.textures[0].img)
		mlx_destroy_image(cb->mlx, cb->map.textures[0].img);
	if (cb->map.textures[1].img)
		mlx_destroy_image(cb->mlx, cb->map.textures[1].img);
	if (cb->map.textures[2].img)
		mlx_destroy_image(cb->mlx, cb->map.textures[2].img);
	if (cb->map.textures[3].img)
		mlx_destroy_image(cb->mlx, cb->map.textures[3].img);
}

void	free_cords(t_cb *cb)
{
	void	*ptr;

	if (cb->cords)
	{
		ptr = cb->cords;
		while (cb->cords)
		{
			ptr = cb->cords->next;
			free(cb->cords);
			cb->cords = ptr;
		}
	}
}

void	exit_cub(t_cb *cb, char *str, int status_code)
{
	free_cords(cb);
	free_map(cb);
	if (cb->img.img)
		mlx_destroy_image(cb->mlx, cb->img.img);
	if (cb->win)
		mlx_destroy_window(cb->mlx, cb->win);
	if (cb->mlx)
		mlx_destroy_display(cb->mlx);
	free(cb->mlx);
	free(cb->keybinds);
	if (str)
		printf("%s", str);
	if (cb->map.textures_arr)
	{
		free(cb->map.textures_arr[0]);
		free(cb->map.textures_arr[1]);
		free(cb->map.textures_arr[2]);
		free(cb->map.textures_arr[3]);
		free(cb->map.textures_arr[4]);
		free(cb->map.textures_arr[5]);
		free(cb->map.textures_arr);
	}
	exit(status_code);
}
