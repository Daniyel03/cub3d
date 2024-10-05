/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:27:55 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/05 13:30:34 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	str_is_number(char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

// if line found, read until count != i,
void	set_fd(t_parser *parser)
{
	parser->i = 0;
	parser->temp_fd = open(parser->filename, O_RDONLY);
	if (parser->temp_fd == -1)
		exit_parser(parser, NULL);
	while (++parser->i < parser->line_count)
	{
		parser->str = get_next_line(parser->temp_fd);
		if (parser->str == NULL)
			exit_parser(parser, "malloc fail\n");
		free(parser->str);
		parser->str = NULL;
	}
	parser->i = 0;
}

// reads until no empty line, returns 0 if fd is at its end
int	read_until_not_empty(t_parser *parser)
{
	set_fd(parser);
	parser->temp = get_next_line(parser->temp_fd);
	if (parser->temp == NULL && parser->line_count == 0)
		exit_parser(parser, "empty file");
	if (parser->line_count == 0)
		parser->line_count = 1;
	while (parser->temp)
	{
		if (parser->temp == NULL)
			return (free(parser->temp), parser->temp = NULL, 0);
		if (empty_line(parser->temp))
			return (free(parser->temp), set_fd(parser), 1);
		free(parser->temp);
		parser->temp = NULL;
		parser->temp = get_next_line(parser->temp_fd);
		parser->line_count++;
	}
	return (0);
}

void	free_map_texture_arr(t_parser *parser)
{
	if (parser->cb->map.textures_arr)
	{
		free(parser->cb->map.textures_arr[0]);
		parser->cb->map.textures_arr[0] = NULL;
		free(parser->cb->map.textures_arr[1]);
		parser->cb->map.textures_arr[1] = NULL;
		free(parser->cb->map.textures_arr[2]);
		parser->cb->map.textures_arr[2] = NULL;
		free(parser->cb->map.textures_arr[3]);
		parser->cb->map.textures_arr[3] = NULL;
		free(parser->cb->map.textures_arr[4]);
		parser->cb->map.textures_arr[4] = NULL;
		free(parser->cb->map.textures_arr[5]);
		parser->cb->map.textures_arr[5] = NULL;
		free(parser->cb->map.textures_arr);
		parser->cb->map.textures_arr = NULL;
	}
}

void	exit_parser(t_parser *parser, char *errormessage)
{
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
	free_map_texture_arr(parser);
	if (parser->str)
		free(parser->str);
	if (parser->file)
		free(parser->file);
	free_cords(parser->cb);
	free_map(parser->cb);
	ft_putstr_fd("Error\n", 2);
	if (errormessage)
		ft_putstr_fd(errormessage, 2);
	exit(1);
}
