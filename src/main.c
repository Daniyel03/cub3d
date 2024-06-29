/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/06/29 11:42:14 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

    //go through string until . ,check if ends with cub,
    //check if file exists and opens with read rights, assign it to fd and 
    // read completely and check if only 0 and 1 digits while counting lines for alloc 2d array
    //parse each line to parser, count ints, alloc for int array and set them

void    get_fd(t_cb *cb, char **argv)
{
    int i = 0;
    while (argv[1][i] && argv[1][i] != '.')
        i++;
    if (argv[1][i] != '.')
        return ;
    if (ft_strncmp(argv[1] + i, ".cub", ft_strlen(argv[1] + i)))
        return ;
    cb->map.fd = open(argv[1], O_RDONLY);
    // perror("");
    if (cb->map.fd == -1)
        return ;
}

void    alloc_array(t_cb *cb)//close when done reading
{
    char *str;
    int count = 0;
    
    cb->map.arr = malloc(sizeof(int *));
    str = get_next_line(cb->map.fd);
    while(str[count])
        count++;
    
    printf("%d\n", count);
}

void	get_map(t_cb *cb, char **argv)
{
    get_fd(cb, argv);
    alloc_array(cb);
    //create_map w floodfill
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

void init_struct(t_cb *cb)
{
	ft_bzero(cb, sizeof(t_cb));
    //cb->map = malloc(sizeof(t_map));
    ft_bzero(&cb->map, sizeof(t_map));
}

void	cub3d(char **argv)
{
	t_cb	cb;

    init_struct(&cb);
	// ft_bzero(&cb, sizeof(t_cb));
    // ft_bzero(&cb.map, sizeof(t_map));
	get_map(&cb, argv);
	init_mlx(&cb);
	init_keybinds(&cb);
	setup_hooks(&cb);
	mlx_loop(cb.mlx);
}

int	main(int argc, char **argv)
{
    // perror("");
	if (argc == 2)
		cub3d(argv);
	return (0);
}