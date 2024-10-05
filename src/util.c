/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:06:44 by hrother           #+#    #+#             */
/*   Updated: 2024/10/04 22:56:50 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday");
		return (0);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	set_deltatime(t_cb *cb)
{
	long		new_time;
	static long	old_time = 0;

	new_time = get_time_ms();
	if (new_time == 0)
		exit_cub(cb, NULL, 1);
	cb->deltatime = (new_time - old_time) / 1000.0;
	printf("fps: %f\n", 1 / cb->deltatime);
	old_time = new_time;
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
		return (rot - 2 * PI);
	else if (rot < 0)
		return (rot + 2 * PI);
	return (rot);
}
