/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:06:44 by hrother           #+#    #+#             */
/*   Updated: 2024/06/29 18:34:36 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		perror("gettimeofday"); // is this protection enough?
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	exit_cub(t_cb *cb, char *str)
{
	if (cb->img.img)
		mlx_destroy_image(cb->mlx, cb->img.img);
	if (cb->win)
		mlx_destroy_window(cb->mlx, cb->win);
	if (cb->mlx)
		mlx_destroy_display(cb->mlx);
	free(cb->mlx);
	free(cb->keybinds);

	if (cb->map.arr)
	{
		if (cb->map.y)
			while (cb->map.y)
				free(cb->map.arr[--cb->map.y]);
		free(cb->map.arr);
	}
	if (str)
		printf("%s", str);

	if (cb->cords)
	{
		void *ptr = cb->cords;
		while (cb->cords)
		{
			ptr = cb->cords->next;
			free(cb->cords);
			cb->cords = ptr;
		}
		// free(cb->cords);
	}


	free(cb->map.textures_arr[0]);
	cb->map.textures_arr[0] = NULL;
	free(cb->map.textures_arr[1]);
	cb->map.textures_arr[1] = NULL;
	free(cb->map.textures_arr[2]);
	cb->map.textures_arr[2] = NULL;
	free(cb->map.textures_arr[3]);
	cb->map.textures_arr[3] = NULL;
	free(cb->map.textures_arr[4]);
	cb->map.textures_arr[4] = NULL;
	free(cb->map.textures_arr[5]);
	cb->map.textures_arr[5] = NULL;
	free(cb->map.textures_arr);
	cb->map.textures_arr = NULL;


	exit(0); // TODO: exit with errorcode when an error occured
}

void	print_map(t_map map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map.y)
	{
		x = 0;
		while (map.arr[y][x] != -1)
		{
			printf("%d ", map.arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

double	clamp_rot(double rot)
{
	if (rot >= 2 * PI)
		return rot - 2 * PI;
	else if (rot < 0)
		return rot + 2 * PI;
	return rot;
}
