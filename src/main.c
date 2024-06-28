/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:08:33 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 18:20:20 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

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
    cb->map.filename = argv[1];
    cb->map.fd = open(cb->map.filename, O_RDONLY);
    // perror("");
    if (cb->map.fd == -1)
        return ;
}

void    alloc_array(t_cb *cb)//close when done reading
{
    char *str;
    int count = 0;
    int i = 0;
    int temp = open(cb->map.filename, O_RDONLY);
    while (get_next_line(temp))
        count++;
    // printf("%d\n", count);
    close(temp);

    
    cb->player_pos.x = -1;
    cb->player_pos.y = -1;

    cb->map.arr = malloc(sizeof(int *) * count);
    count = 0;
    temp = 0;
    str = get_next_line(cb->map.fd);
    while (str)
    {
        count = 0;
        while(str[count])
        {
            if (str[count] != 'N' && str[count] != '1' && str[count] != '2' && str[count] != ' ' && str[count] != '\0' && str[count] != '\n')
                return ;
            if (str[count] == 'N')
            {
                if (cb->player_pos.x != -1)
                    return ;
                cb->player_pos.x = count;
                cb->player_pos.y = temp;
            }
            count++;
            temp++;
        }
        if (str[count - 1] == '\n')
            count--;
        printf("%d\n", count);
        cb->map.arr[i++] = malloc(sizeof(int) * count);
        str = get_next_line(cb->map.fd);
    }
    
    // printf("%s\n", str);

    // temp = open(cb->map.filename, O_RDONLY);
    // while (get_next_line(temp))
    //     count++;
    // printf("%d\n", count);
    // close(temp);
    
    // str = get_next_line(cb->map.fd);

    

    // while(str[count])
    // {
    //     if (str[count] == 'p')
    //         cb->player_pos.x = count;
    //     count++;
    // }
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
    // cb->map = malloc(sizeof(t_map));
    ft_bzero(&cb->map, sizeof(t_map));
}

void	cub3d(char **argv)
{
	t_cb	cb;

    init_struct(&cb);
	get_map(&cb, argv);
	// init_mlx(&cb);
	// init_keybinds(&cb);
	// setup_hooks(&cb);
	// mlx_loop(cb.mlx);
}

int	main(int argc, char **argv)
{
    // perror("");
	if (argc == 2)
		cub3d(argv);
	return (0);
}