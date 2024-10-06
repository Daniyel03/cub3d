/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:27:18 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/06 16:35:32 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

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

void	check_file_and_iterate(t_parser *parser)
{
	if (close(parser->temp_fd) == -1)
		exit_parser(parser, NULL);
	parser->temp_fd = open(parser->file, O_RDONLY);
	if (parser->temp_fd == -1)
		exit_parser(parser, "texture file doesnt exist\n");
	if (ft_strlen(parser->file) <= 4 || ft_strncmp(parser->file
			+ ft_strlen(parser->file) - 4, ".xpm", 5))
		exit_parser(parser, "not a proper .xpm file\n");
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
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
	while (!ft_isspace(parser->temp[parser->i]) && parser->temp[parser->i] != '\0')
		parser->i++;
	parser->file = ft_substr(parser->temp, 0, parser->i);
	if (parser->file == NULL)
		exit_parser(parser, NULL);
	parser->i = 0;
	parser->temp = parser->str;
	iterate_until_no_space(&parser->temp);
	if (parser->temp[0] == 'F' || parser->temp[0] == 'C')
		rgb_to_hexadecimal(parser);
	else
		check_file_and_iterate(parser);
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
}

void	check_texture(t_parser *parser)
{
	parser->str = get_next_line(parser->temp_fd);
	if (parser->str == NULL)
		exit_parser(parser, NULL);
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
