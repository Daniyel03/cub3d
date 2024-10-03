/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:04:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/02 13:52:46 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"
#include <fcntl.h>

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

void	validate_input(t_parser *parser, char **argv)
{
	get_filename(parser, argv);
	validate_textures(parser);
	alloc_array(parser);
	if(flood_fill(parser) == FAILURE)
		exit_parser(parser, "map not surrounded by walls\n");
	print_map(parser->cb->map);
}

void	parser(t_cb *cb, char **argv)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	parser.cb = cb;
	parser.cb->map.textures_arr = ft_calloc(6, sizeof(char **));
	if (!parser.cb->map.textures_arr)
		exit_parser(&parser, "malloc fail\n");
	validate_input(&parser, argv);
	print_textures(&parser);
	close(parser.temp_fd);
}