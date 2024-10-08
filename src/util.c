/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:06:44 by hrother           #+#    #+#             */
/*   Updated: 2024/10/08 16:20:31 by dscholz          ###   ########.fr       */
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
	old_time = new_time;
}

double	clamp_rot(double rot)
{
	if (rot >= 2 * PI)
		return (rot - 2 * PI);
	else if (rot < 0)
		return (rot + 2 * PI);
	return (rot);
}

void	free_ptr_arr(void **arr, int size)
{
	while (size--)
	{
		free(arr[size]);
	}
	free(arr);
}
