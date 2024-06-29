/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:04:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/06/29 12:03:27 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validate_path(t_cb *cb, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (argv[1][i] != '.')
		return (exit_cub(cb, "file has to be in .cub format\n"));
	if (ft_strncmp(argv[1] + i, ".cub", 5))
		return (exit_cub(cb, "file has to be in .cub format\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_cub(cb, "file doesn't exist\n"));
	else
		close(fd);
	cb->map.filename = argv[1];
}

void	iterate_line(t_cb *cb, int *x, char *str)
{
	while (str[(*x)] && str[(*x)] != '\n')
	{
		if (str[(*x)] != 'N' && str[(*x)] != '0' && str[(*x)] != '1'
			&& str[(*x)] != ' ' && str[(*x)] != '\0' && str[(*x)] != '\n')
			return ;
		if (str[(*x)] == 'N')
		{
			if (cb->player_pos.x != -1)
				return ;
			cb->player_pos.x = (*x);
			cb->player_pos.y = cb->map.y;
		}
		(*x)++;
	}
}

void	validate_input(t_cb *cb)
{
	char	*str;
	int		temp_fd;
	int		x;
    
	cb->map.y = 0;
	x = 0;
	temp_fd = open(cb->map.filename, O_RDONLY);
	if (temp_fd == -1)
		return (exit_cub(cb, NULL));
	str = get_next_line(temp_fd);
	while (str)
	{
		x = 0;
		iterate_line(cb, &x, str);
		cb->map.arr[cb->map.y] = malloc(sizeof(int) * x);
		if (!cb->map.arr[cb->map.y++])
			return (exit_cub(cb, NULL));
		free(str);
		str = get_next_line(temp_fd);
	}
	if (close(temp_fd) == -1)
		return (exit_cub(cb, NULL));
}

void	fill_lines(t_cb *cb)
{
	int		temp_fd;
	char	*str;
	char	*c;
	int		x;
	int		y;

	x = -1;
	y = 0;
	temp_fd = open(cb->map.filename, O_RDONLY);
	str = get_next_line(temp_fd);
	while (str)
	{
		while (str[++x] && str[x] != '\n')
		{
			c = ft_substr(str, x, 1);
			if (!ft_strncmp(c, " ", 1))
				cb->map.arr[y][x] = 2;
			else
				cb->map.arr[y][x] = ft_atoi(c);
			free(c);
			printf("%d", cb->map.arr[y][x]);
		}
		y++;
		str = get_next_line(temp_fd);
		x = -1;
		printf("\n");
	}
}

void	alloc_array(t_cb *cb)
{
	int		count;
	int		temp_fd;
	char	*temp;

	count = 0;
	temp_fd = open(cb->map.filename, O_RDONLY);
	if (temp_fd == -1)
		return (exit_cub(cb, NULL));
	temp = get_next_line(temp_fd);
	while ((temp) && count++ != -1)
	{
		free(temp);
		temp = get_next_line(temp_fd);
	}
	cb->map.arr = malloc(sizeof(int *) * count);
	if (!cb->map.arr)
		return (exit_cub(cb, NULL));
	*cb->map.arr = NULL;
	if (close(temp_fd) == -1)
		return (exit_cub(cb, NULL));
	validate_input(cb);
	fill_lines(cb);
}
