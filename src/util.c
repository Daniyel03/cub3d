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

#include "cub3d.h"

double distance(t_vec2 a, t_vec2 b)
{
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
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
    exit(0); //TODO: exit with errorcode when an error occured
}
