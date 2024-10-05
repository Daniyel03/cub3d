/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/10/05 14:32:38 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	hex_atoi(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 48);
	return (c - 87);
}

int	hex_to_int(char *str)
{
	int	res;
	int	power;

	res = 0;
	power = 5;
	str += 2;
	while (*str)
		res += hex_atoi(*str++) * (int)pow((int)16, (int)power--);
	return (res);
}

void	cub3d(char **argv)
{
	t_cb	cb;

	init_struct(&cb);
	parser(&cb, argv);
	init_mlx(&cb);
	cb.map.textures[0] = init_texture(cb.map.textures_arr[0], &cb);
	cb.map.textures[1] = init_texture(cb.map.textures_arr[1], &cb);
	cb.map.textures[2] = init_texture(cb.map.textures_arr[2], &cb);
	cb.map.textures[3] = init_texture(cb.map.textures_arr[3], &cb);
	if (!cb.map.textures[0].img || !cb.map.textures[1].img
		|| !cb.map.textures[2].img || !cb.map.textures[3].img)
		exit_cub(&cb, "invalid texture\n", 1);
	cb.map.ceil_color = hex_to_int(cb.map.textures_arr[4]);
	cb.map.floor_color = hex_to_int(cb.map.textures_arr[5]);
	init_keybinds(&cb);
	setup_hooks(&cb);
	mlx_loop(cb.mlx);
	exit_cub(&cb, "success\n", 1);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		cub3d(argv);
	return (0);
}
