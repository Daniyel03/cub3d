/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 00:14:07 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map(t_cb *cb, char **argv)
{
	int	i;

	(void)cb;
	i = 0;
	while (argv[1][i])
		printf("%c\n", argv[1][i++]);
}

int	init_mlx(t_cb *cb)
{
	cb->mlx = mlx_init();
	if (!cb->mlx)
		return (-1);
	cb->win = mlx_new_window(cb->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cb->win)
		return (-1);
	cb->img.img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->img.addr = mlx_get_data_addr(cb->img.img, &cb->img.bits_per_pixel,
			&cb->img.line_length, &cb->img.endian);
	if (cb->img.img == NULL || cb->img.addr == NULL)
		return (-1); // --> exit
	return (0);
}

void	cub3d(char **argv)
{
	t_cb	cb;

	ft_bzero(&cb, sizeof(t_cb));
	get_map(&cb, argv);
	init_mlx(&cb);
	mlx_loop(cb.mlx);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		cub3d(argv);
	return (0);
}