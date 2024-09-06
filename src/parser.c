/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:04:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/09/06 20:35:15 by dscholz          ###   ########.fr       */
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
		return (1);
	if (parser->temp[0] == 'S' && parser->temp[1] == 'O')
		return (1);
	if (parser->temp[0] == 'E' && parser->temp[1] == 'A')
		return (1);
	if (parser->temp[0] == 'W' && parser->temp[1] == 'E')
		return (1);
	if (parser->temp[0] == 'C')
		return (1);
	if (parser->temp[0] == 'F')
		return (1);
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

void	check_commas(t_parser *parser)
{
	parser->i = 0;
	while (parser->temp[parser->i])
	{
		if (parser->temp[parser->i] == ',' && !ft_isdigit(parser->temp[parser->i
				+ 1]))
			exit_cub(parser->cb, "false rgb input\n");
		parser->i++;
	}
}


// void	str_array_join(t_parser *parser)
// {
// 	parser->temp = NULL;
// 	parser->i = 0;
// 	while (parser->numbers[parser->i])
// 	{
// 		if (parser->numbers[parser->i + 1])
// 		{
// 			if (parser->number)
// 			{
// 				parser->temp = ft_strjoin(parser->number,
						// ft_strjoin(parser->numbers[parser->i],
						// 	parser->numbers[parser->i + 1]));
// 				free(parser->number);
// 				parser->number = parser->temp;
// 				parser->temp = NULL;
// 			}
// 			else
// 				parser->number = ft_strjoin(parser->numbers[parser->i],
						// parser->numbers[parser->i + 1]);
// 			parser->i += 2;
// 		}
// 		else
// 			return ;
// 	}
// }

void	check_digit(t_parser *parser)
{
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
	while (!ft_isspace(parser->temp[parser->i]))
		parser->i++;
	if (!ft_isdigit(parser->file[0]) || !ft_isdigit(parser->file[parser->i
			- 1]))
		exit_cub(parser->cb, "false rgb input\n");
	check_commas(parser);
	parser->i = 0;
	while (parser->numbers[parser->i]
		&& str_is_number(parser->numbers[parser->i])
		&& ft_atoi(parser->numbers[parser->i]))
	{
		if (!str_is_number(parser->numbers[parser->i])
			|| (ft_atoi(parser->numbers[parser->i]) > 255
				|| ft_atoi(parser->numbers[parser->i]) < 0))
			exit_cub(parser->cb, "invalid rgb input, just numbers 0-255\n");
		parser->i++;
	}
	if (parser->i != 3 || parser->numbers[parser->i] != NULL)
		exit_cub(parser->cb, "invalid rgb input\n");
}

	// // strjoin, convert to hexa recursively
	// 12345678abcdefgh, while num > 16, num % 16, recursiv(num / 16)
// void	numarray_to_hexadecimal(t_parser *parser)
// {
//     char *table = "0123456789abcdef";
//     char *temp1;
//     char *temp2;
//     if (num < 16)
//     {
//         temp1 = ft_substr(table, num, 1);
//         temp2 = ft_strjoin((*str), temp1);
//         free((*str));
//         free(temp1);
//         (*str) = temp2;
//         temp2 = NULL;
//     }
//     else
//     {
//         h(str, num / 16);
//         h(str, num % 16);
//     }
// }

void	numarray_to_hexadecimal(t_parser *parser)
{
    char *table = "0123456789abcdef";
    char *temp1;
    char *temp2;
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
		parser->i /= 16;
        numarray_to_hexadecimal(parser);
        parser->i = parser->i % 16;
		numarray_to_hexadecimal(parser);
    }
}


//
void	set_digits(t_parser *parser)
{	
	parser->number = ft_strdup("0x");
	parser->ptr = parser->numbers;
	while (*(char **)parser->ptr)
	{
		parser->i = ft_atoi(*(char **)parser->ptr);
		numarray_to_hexadecimal(parser);
		parser->ptr = (char **)parser->ptr + 1;
	}

	printf("%s\n", parser->number);

	// parser->ptr = parser->numbers;
	// while (*(char **)parser->ptr)
	// {
	// 	printf("%s\n", *(char **)parser->ptr);
	// 	parser->ptr = (char **)parser->ptr + 1;
	// }
}

void	rgb_to_hexadecimal(t_parser *parser)
{
	// parser->file = "0x";
	parser->numbers = ft_split(parser->file, ',');
	check_digit(parser);
	set_digits(parser);
	// free(parser->file);
	// parser->file = NULL;
	// while (parser->numbers[parser->i])
	// 	parser->file = ft_strjoin(parser->numbers[parser->i],
				// parser->numbers[parser->i + 1]);
}

void	set_texture(t_parser *parser)
{
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
	parser->i = 0;
	// while (ft_isspace(parser->temp[parser->i]))
	// 	parser->i++;
	// if (empty_line(parser->temp))
	// 	return ; // invalid texture, character after path
	parser->temp = parser->str;
	iterate_until_no_space(&parser->temp);
	if (parser->temp[0] == 'F' || parser->temp[0] == 'C')
		rgb_to_hexadecimal(parser);
	else
	{
		// if (-1 == open(parser->file, O_RDONLY))
		// 	return ; // file  doesnt exist;
		// 			// should it end with .xpm?
		// set_texture(parser);
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
		return (exit_cub(parser->cb, "map before textures\n"));
	if (!check_direction(parser))
		return (exit_cub(parser->cb, "false texture direction\n"));
	iterate_until_space(&parser->temp);
	if (!empty_line(parser->temp))
		return (exit_cub(parser->cb, "no texture file\n"));
	iterate_until_no_space(&parser->temp);
	test_texture_path(parser);
	// iterate_until_space(&parser->temp);
	// iterate_until_no_space(&parser->temp);
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