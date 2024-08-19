/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:04:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/08/19 13:13:26 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

// void	free_parser(t_parser *parser)
// {
// 	if (parser->fd) || -1
// 		close (parser->fd);
// 	if (parser->parser->temp_fd)
// 		close (parser->parser->temp_fd);
// 	if (parser->last_graphic)
// 		close (parser->last_graphic);
// 	if (parser->fd_textures)
// 		close (parser->fd_textures);
// 	if (parser->fd_map)
// 		close (parser->fd_map);
// }

void	validate_path(t_parser *parser, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (argv[1][i] != '.')
		return (exit_cub(parser->cb, "file has to be in .cub format\n"));
	if (ft_strncmp(argv[1] + i, ".cub", 5))
		return (exit_cub(parser->cb, "file has to be in .cub format\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (exit_cub(parser->cb, "file doesn't exist\n"));
	close(fd);
	parser->filename = argv[1];
}

void	set_player_rot(t_parser *parser, int *x, char *str)
{
	if (str[(*x)] == 'N')
		return (parser->cb->player.rot = PI, (void)0);
	if (str[(*x)] == 'S')
		return (parser->cb->player.rot = 0, (void)0);
	if (str[(*x)] == 'E')
		return (parser->cb->player.rot = PI * 0.5, (void)0);
	if (str[(*x)] == 'W')
		return (parser->cb->player.rot = PI * 1.5, (void)0);
}

void	iterate_line(t_parser *parser, int *x, char *str)
{
	while (str[(*x)] && str[(*x)] != '\n')
	{
		if (!(str[(*x)] == 'N' || str[(*x)] == 'W' || str[(*x)] == 'S'
				|| str[(*x)] == 'E') && str[(*x)] != '0' && str[(*x)] != '1'
			&& str[(*x)] != ' ' && str[(*x)] != '\0' && str[(*x)] != '\n')
			return (close(parser->temp_fd), free(str), 
			exit_cub(parser->cb, "invalid map input, only 0 and 1 allowed\n"));
		if (str[(*x)] == 'N' || str[(*x)] == 'W' || str[(*x)] == 'S'
			|| str[(*x)] == 'E')
		{
			if (parser->cb->player.pos.x != -1)
				return (close(parser->temp_fd), free(str), exit_cub(parser->cb,
						"invalid map input, only one player position\n"));
			parser->cb->player.pos.x = (*x) + 0.5;
			parser->cb->player.pos.y = parser->cb->map.y + 0.5;
			set_player_rot(parser, x, str);
		}
		(*x)++;
	}
}

//

// void	parser_input(t_parser *parser)
// {

// }

void	validate_input(t_parser *parser) // validate_map
{
	char *str;
	int x;

	parser->cb->map.y = 0;
	x = 0;
	parser->temp_fd = open(parser->filename, O_RDONLY);
	if (parser->temp_fd == -1)
		return (exit_cub(parser->cb, NULL));
	str = get_next_line(parser->temp_fd);
	while (str)
	{
		x = 0;
		iterate_line(parser, &x, str);
		parser->cb->map.arr[parser->cb->map.y] = malloc(sizeof(int) * (x + 1));
		if (!parser->cb->map.arr[parser->cb->map.y++])
			return (exit_cub(parser->cb, NULL));
		free(str);
		str = get_next_line(parser->temp_fd);
	}
	if (close(parser->temp_fd) == -1)
		return (exit_cub(parser->cb, NULL));
}

void	fill_lines(t_parser *parser)
{
	char	*str;
	char	*c;
	int		x;
	int		y;

	x = -1;
	y = 0;
	parser->temp_fd = open(parser->filename, O_RDONLY);
	if (parser->temp_fd == -1)
		return (exit_cub(parser->cb, NULL));
	str = get_next_line(parser->temp_fd);
	while (y < parser->cb->map.y)
	{
		while (str[++x] && str[x] != '\n')
		{
			c = ft_substr(str, x, 1);
			if (!ft_strncmp(c, " ", 1))
				parser->cb->map.arr[y][x] = 2;
			else
				parser->cb->map.arr[y][x] = ft_atoi(c);
			free(c);
			// printf("%d", parser->cb->map.arr[y][x]);
		}
		parser->cb->map.arr[y][x] = -1;
		// printf("%d\n", parser->cb->map.arr[y][x]);
		y++;
		free(str);
		str = get_next_line(parser->temp_fd);
		x = -1;
	}
}

void	alloc_array(t_parser *parser)
{
	int		count;
	char	*temp = NULL;

	count = 0;
	parser->temp_fd = open(parser->filename, O_RDONLY);

	if (parser->temp_fd == -1)
		return (exit_cub(parser->cb, NULL));
	temp = get_next_line(parser->temp_fd);
	while ((temp) && count++ != -1)
	{
		free(temp);
		temp = get_next_line(parser->temp_fd);
	}
	parser->cb->map.arr = malloc(sizeof(int *) * count);
	if (!parser->cb->map.arr)
		return (exit_cub(parser->cb, NULL));
	// *parser->cb->map.arr = NULL;
	if (close(parser->temp_fd) == -1)
		return (exit_cub(parser->cb, NULL));
	validate_input(parser);
	fill_lines(parser);
}

void	parser(t_cb *cb, char **argv)
{
	t_parser parser;
	int valid = 0;

	ft_bzero(&parser, sizeof(parser));
	parser.cb = cb;

	validate_path(&parser, argv);
	alloc_array(&parser);
	print_map(parser.cb->map);
	valid = flood_fill(cb);
	print_cord(cb);
	printf("valid map: %d\n", valid);
	print_map(cb->map);
}