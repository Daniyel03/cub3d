/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:04:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/09/06 21:59:49 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <fcntl.h>
#include "../includes/parser.h"

void	get_filename(t_parser *parser, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (i > 4)
		i -= 4;
	if (ft_strncmp(argv[1] + i, ".cub", 5))
		return (exit_parser(parser, "file has to be in .cub format\n"));
	parser->temp_fd = open(argv[1], O_RDONLY);
	if (parser->temp_fd == -1)
		return (exit_parser(parser, "file doesn't exist\n"));
	parser->filename = argv[1];
}

void	is_dir_set(t_parser *parser)
{
	if (parser->cb->map.textures_arr[parser->i])
		return (exit_parser(parser, 
			"direction already set / exists more than once\n"));
}

int	check_direction(t_parser *parser)
{
	if (parser->temp[0] == 'N' && parser->temp[1] == 'O'
		&& ft_isspace(parser->temp[2]))
		return (parser->i = 0, is_dir_set(parser), 1);
	if (parser->temp[0] == 'S' && parser->temp[1] == 'O'
		&& ft_isspace(parser->temp[2]))
		return (parser->i = 2, is_dir_set(parser), 1);
	if (parser->temp[0] == 'E' && parser->temp[1] == 'A'
		&& ft_isspace(parser->temp[2]))
		return (parser->i = 1, is_dir_set(parser), 1);
	if (parser->temp[0] == 'W' && parser->temp[1] == 'E'
		&& ft_isspace(parser->temp[2]))
		return (parser->i = 3, is_dir_set(parser), 1);
	if (parser->temp[0] == 'C' && ft_isspace(parser->temp[1]))
		return (parser->i = 4, is_dir_set(parser), 1);
	if (parser->temp[0] == 'F' && ft_isspace(parser->temp[1]))
		return (parser->i = 5, is_dir_set(parser), 1);
	return (0);
}

void	check_commas(t_parser *parser)
{
	parser->i = 0;
	while (parser->temp[parser->i])
	{
		if (parser->temp[parser->i] == ',' && !ft_isdigit(parser->temp[parser->i
				+ 1]))
			exit_parser(parser, "false rgb input\n");
		parser->i++;
	}
}

void	check_digit(t_parser *parser)
{
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
	while (!ft_isspace(parser->temp[parser->i]))
		parser->i++;
	if (!ft_isdigit(parser->file[0]) || !ft_isdigit(parser->file[parser->i
			- 1]))
		exit_parser(parser, "false rgb input\n");
	check_commas(parser);
	parser->i = 0;
	while (parser->numbers[parser->i]
		&& str_is_number(parser->numbers[parser->i]))
	{
		if (!str_is_number(parser->numbers[parser->i])
			|| (ft_atoi(parser->numbers[parser->i]) > 255
				|| ft_atoi(parser->numbers[parser->i]) < 0))
			exit_parser(parser, "invalid rgb input, just numbers 0-255\n");
		parser->i++;
	}
	if (parser->i != 3 || parser->numbers[parser->i] != NULL)
		exit_parser(parser, "invalid rgb input\n");
}

void	numarray_to_hexadecimal(t_parser *parser)
{
	char	*table;
	char	*temp1;
	char	*temp2;
	int		temp;

	table = "0123456789abcdef";
	if (parser->i < 16)
	{
		temp1 = ft_substr(table, parser->i, 1);
		temp2 = ft_strjoin(parser->number, temp1);
		free(parser->number);
		free(temp1);
		parser->number = temp2;
		temp2 = NULL;
	}
	else
	{
		temp = parser->i;
		parser->i /= 16;
		numarray_to_hexadecimal(parser);
		parser->i = temp % 16;
		numarray_to_hexadecimal(parser);
	}
}

void	append_zero(t_parser *parser)
{
	char	*temp;

	temp = ft_strjoin(parser->number, "0");
	free(parser->number);
	parser->number = temp;
	temp = NULL;
}

void	set_digits(t_parser *parser)
{
	parser->number = ft_strdup("0x");
	parser->ptr = parser->numbers;
	while (*(char **)parser->ptr)
	{
		parser->i = ft_atoi(*(char **)parser->ptr);
		if (parser->i < 16)
			append_zero(parser);
		numarray_to_hexadecimal(parser);
		parser->ptr = (char **)parser->ptr + 1;
	}
}

void	rgb_to_hexadecimal(t_parser *parser)
{
	parser->numbers = ft_split(parser->file, ',');
	check_digit(parser);
	set_digits(parser);
	free(parser->file);
	parser->file = NULL;
}

void	set_texture_reset(t_parser *parser)
{
	free(parser->str);
	parser->str = NULL;
	parser->i = 0;
	if (parser->numbers)
	{
		while (parser->numbers[parser->i])
		{
			free(parser->numbers[parser->i]);
			parser->numbers[parser->i++] = NULL;
		}
		free(parser->numbers);
		parser->numbers = NULL;
	}
	parser->file = NULL;
	parser->temp = NULL;
}

void	set_texture(t_parser *parser)
{
	parser->temp = parser->str;
	iterate_until_no_space(&parser->temp);
	if ((*parser->temp == 'N' && parser->temp[1] == 'O'))
		parser->cb->map.textures_arr[0] = parser->file;
	if (*parser->temp == 'S' && parser->temp[1] == 'O')
		parser->cb->map.textures_arr[2] = parser->file;
	if (*parser->temp == 'E' && parser->temp[1] == 'A')
		parser->cb->map.textures_arr[1] = parser->file;
	if (*parser->temp == 'W' && parser->temp[1] == 'E')
		parser->cb->map.textures_arr[3] = parser->file;
	if (parser->temp[0] == 'C')
		parser->cb->map.textures_arr[4] = parser->number;
	if (parser->temp[0] == 'F')
		parser->cb->map.textures_arr[5] = parser->number;
	set_texture_reset(parser);
}

void	test_texture_path(t_parser *parser)
{
	while (!ft_isspace(parser->temp[parser->i]))
		parser->i++;
	parser->file = ft_substr(parser->temp, 0, parser->i);
	parser->i = 0;
	parser->temp = parser->str;
	iterate_until_no_space(&parser->temp);
	if (parser->temp[0] == 'F' || parser->temp[0] == 'C')
		rgb_to_hexadecimal(parser);
	else
	{
		(close(parser->temp_fd));
		parser->temp_fd = open(parser->file, O_RDONLY);
		if (parser->temp_fd == -1)
			exit_parser(parser, "texture file doesnt exist\n");
		// (close(parser->temp_fd));
		iterate_until_space(&parser->temp);
		iterate_until_no_space(&parser->temp);
	}
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
}

void	check_texture(t_parser *parser)
{
	parser->str = get_next_line(parser->temp_fd);
	parser->line_count++;
	parser->temp = parser->str;
	iterate_until_no_space(&parser->temp);
	if (ft_isdigit(*parser->temp) || ft_isdigit(*parser->temp + 1))
		return (exit_parser(parser, "map before textures\n"));
	if (!check_direction(parser))
		return (exit_parser(parser, "false texture direction\n"));
	iterate_until_space(&parser->temp);
	if (!empty_line(parser->temp))
		return (exit_parser(parser, "no texture file\n"));
	iterate_until_no_space(&parser->temp);
	test_texture_path(parser);
	if (parser->temp[0] != '\0')
		return (exit_parser(parser, 
			"too many elements, just pass direction and texturefile\n"));
}

void	validate_textures(t_parser *parser)
{
	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);

	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);

	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);
	
	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);
	
	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);
	
	read_until_not_empty(parser);
	check_texture(parser);
	set_texture(parser);

	
}

void	validate_input(t_parser *parser, char **argv)
{
	get_filename(parser, argv);
	validate_textures(parser);
	alloc_array(parser);
	flood_fill(parser->cb);
	print_map(parser->cb->map);
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
			return (close(parser->temp_fd), free(str), exit_parser(parser,
					"invalid map input, only 0 and 1 allowed\n"));
		if (str[(*x)] == 'N' || str[(*x)] == 'W' || str[(*x)] == 'S'
			|| str[(*x)] == 'E')
		{
			if (parser->cb->player.pos.x != -1)
				return (close(parser->temp_fd), free(str), exit_parser(parser,
						"invalid map input, only one player position\n"));
			parser->cb->player.pos.x = (*x) + 0.5;
			parser->cb->player.pos.y = parser->cb->map.y + 0.5;
			set_player_rot(parser, x, str);
		}
		(*x)++;
	}
}

void	fill_lines(t_parser *parser)
{
	char	*str;
	char	*c;
	int		x;
	int		y;

	x = -1;
	y = 0;


	parser->i = parser->map_line;
	set_fd(parser);

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
		}
		parser->cb->map.arr[y][x] = -1;
		y++;
		free(str);
		str = get_next_line(parser->temp_fd);
		x = -1;
	}
}

void	validate_alloc_lines(t_parser *parser)
{
	char	*str;
	int		x;

	parser->cb->map.y = 0;
	x = 0;
	parser->i = parser->map_line;
	set_fd(parser);
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
}

void	alloc_array(t_parser *parser)
{
	int		count;
	char	*temp;

	temp = NULL;
	count = 0;

	set_fd(parser);
	read_until_not_empty(parser);
	parser->map_line = parser->i;

	temp = get_next_line(parser->temp_fd);
	while ((temp) && count++ != -1)
	{
		free(temp);
		temp = get_next_line(parser->temp_fd);
	}
	parser->cb->map.arr = malloc(sizeof(int *) * count);
	if (!parser->cb->map.arr)
		return (exit_parser(parser, NULL));
	if (close(parser->temp_fd) == -1)
		return (exit_parser(parser, NULL));
	validate_alloc_lines(parser);
	fill_lines(parser);
}

void	parser(t_cb *cb, char **argv)
{
	t_parser parser;

	ft_bzero(&parser, sizeof(parser));
	parser.cb = cb;
	parser.cb->map.textures_arr = ft_calloc(6, sizeof(char **));

	validate_input(&parser, argv);
	print_textures(&parser);
	close(parser.temp_fd);
}