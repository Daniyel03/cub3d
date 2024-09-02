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

void	get_filename(t_parser *parser, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (argv[1][i] != '.')
		return (exit_cub(parser->cb, "file has to be in .cub format\n"));
	if (ft_strncmp(argv[1] + i, ".cub", 5))
		return (exit_cub(parser->cb, "file has to be in .cub format\n"));
	parser->temp_fd = open(argv[1], O_RDONLY);
	if (parser->temp_fd == -1)
		return (exit_cub(parser->cb, "file doesn't exist\n"));
	parser->filename = argv[1];
}

// only
// 1. NEWSFC 2. OA 3.

int	check_direction(t_parser *parser)
{
	if (parser->temp[0] == 'N' && parser->temp[1] == 'O')
		return (parser->temp += 2, 1);
	if (parser->temp[0] == 'S' && parser->temp[1] == 'O')
		return (parser->temp += 2, 1);
	if (parser->temp[0] == 'E' && parser->temp[1] == 'A')
		return (parser->temp += 2, 1);
	if (parser->temp[0] == 'W' && parser->temp[1] == 'E')
		return (parser->temp += 2, 1);
	if (parser->temp[0] == 'C')
		return (parser->temp += 1, 1);
	if (parser->temp[0] == 'F')
		return (parser->temp += 1, 1);
	return (0);
}

t_img	init_texture(char *filename, t_cb *cb)
{
	t_img	texture;

	texture.img = mlx_xpm_file_to_image(cb->mlx, filename, &texture.width,
			&texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_length, &texture.endian);
	return (texture);
}

void	rgb_to_hexadecimal(t_parser *parser)
{
	// parser->file = "0x";
	char **numbers = ft_split(parser->file, ',');
	while (*numbers)
		printf("%s\n", *numbers++);
}

void	set_texture(t_parser *parser)
{
	parser->temp = parser->str;
	while (ft_isspace(*parser->temp))
		parser->temp++;
	if (*parser->temp == 'N' && *parser->temp + 1 == 'O')
		parser->i = 0;
	if (*parser->temp == 'S' && *parser->temp + 1 == 'O')
		parser->i = 2;
	if (*parser->temp == 'E' && *parser->temp + 1 == 'A')
		parser->i = 1;
	if (*parser->temp == 'W' && *parser->temp + 1 == 'E')
		parser->i = 3;
	parser->cb->map.textures[parser->i] = init_texture(parser->filename,
			parser->cb);
}

// how to set each texture ->set texture after check texture
void	test_texture_path(t_parser *parser)
{
	while (!ft_isspace(parser->temp[parser->i]))
		parser->i++;
	parser->file = ft_substr(parser->temp, 0, parser->i);
	// while (ft_isspace(parser->temp[parser->i]))
	// 	parser->i++;
	// if (empty_line(parser->temp))
	// 	return ; // invalid texture, character after path
	if (parser->temp[0] == 'F' || parser->temp[0] == 'C')
		return rgb_to_hexadecimal(parser);
	if (-1 == open(parser->file, O_RDONLY))
		return ; // file  doesnt exist;
				// should it end with .xpm?	
	set_texture(parser);
	parser->i = 0;
}

void	check_texture(t_parser *parser)
{
	parser->str = get_next_line(parser->temp_fd);
	parser->line_count++;
	parser->temp = parser->str;
	while (ft_isspace(*parser->temp))
		parser->temp++;
	if (ft_isdigit(*parser->temp) || ft_isdigit(*parser->temp + 1))
		return (exit_cub(parser->cb, "map before textures\n"));
	if (!check_direction(parser))
		return (exit_cub(parser->cb, "false texture direction\n"));
	// while (ft_isspace(*parser->temp))
	// 	parser->temp++;
	if (!empty_line(parser->temp))
		return (exit_cub(parser->cb, "no texture file\n"));
	test_texture_path(parser);
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	if (parser->temp[0] != '\0')
		return (exit_cub(parser->cb, 
		"too many elements, just pass direction and texturefile\n"));
	parser->graphics_count++;
}

// void	set_texture(t_parser *parser)
// {

// }

void	validate_textures(t_parser *parser)
{
	
	read_until_not_empty(parser);
	check_texture(parser);
	// set_texture(parser);
	read_until_not_empty(parser);
	check_texture(parser);
	read_until_not_empty(parser);
	check_texture(parser);
	// read_until_not_empty(parser);
	// check_texture(parser);
	// read_until_not_empty(parser);
	// check_texture(parser);
	// read_until_not_empty(parser);
	// check_texture(parser);
	// if ()
}

void	validate_input(t_parser *parser, char **argv)
{
	// char	*str;
	get_filename(parser, argv);
	validate_textures(parser);
	// free(str); parser->line_count++;
	// read_until_not_empty(parser);
	// str = get_next_line(parser->temp_fd);
	// printf("%s\n", str);
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
			return (close(parser->temp_fd), free(str), exit_cub(parser->cb,
					"invalid map input, only 0 and 1 allowed\n"));
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

// void	validate_input(t_parser *parser) // validate_map
// {
// 	char *str;
// 	int x;

// 	parser->cb->map.y = 0;
// 	x = 0;
// 	parser->temp_fd = open(parser->filename, O_RDONLY);
// 	if (parser->temp_fd == -1)
// 		return (exit_cub(parser->cb, NULL));
// 	str = get_next_line(parser->temp_fd);
// 	while (str)
// 	{
// 		x = 0;
// 		iterate_line(parser, &x, str);
// 		parser->cb->map.arr[parser->cb->map.y] = malloc(sizeof(int) * (x + 1));
// 		if (!parser->cb->map.arr[parser->cb->map.y++])
// 			return (exit_cub(parser->cb, NULL));
// 		free(str);
// 		str = get_next_line(parser->temp_fd);
// 	}
// 	if (close(parser->temp_fd) == -1)
// 		return (exit_cub(parser->cb, NULL));
// }

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
	char	*temp;

	temp = NULL;
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
	fill_lines(parser);
}

void	parser(t_cb *cb, char **argv)
{
	t_parser parser;
	// int valid = 0;

	ft_bzero(&parser, sizeof(parser));
	parser.cb = cb;

	validate_input(&parser, argv);
	// alloc_array(&parser);
	// print_map(parser.cb->map);
	// valid = flood_fill(cb);
	// print_cord(cb);
	// printf("valid map: %d\n", valid);
	// print_map(cb->map);
}