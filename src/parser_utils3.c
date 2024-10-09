/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:32:24 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/09 14:08:57 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

void	check_digit(t_parser *parser)
{
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
	while (!ft_isspace(parser->temp[parser->i]) && parser->temp[parser->i])
		parser->i++;
	if (!ft_isdigit(parser->file[0])
		|| !ft_isdigit(parser->file[parser->i - 1]))
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
		if ((*x) > 500)
			exit_parser(parser, "map to big, x > 500\n");
	}
}

void	next_line(t_parser *parser, char **str, int *y, int *x)
{
	parser->cb->map.arr[(*y)][(*x)] = -1;
	(*y)++;
	free((*str));
	(*str) = NULL;
	(*str) = get_next_line(parser->temp_fd);
	(*x) = -1;
}

void	fill_line_prep(t_parser *parser, char **str, int *y, int *x)
{
	(*x) = -1;
	(*y) = 0;
	parser->i = parser->map_line;
	set_fd(parser);
	(*str) = get_next_line(parser->temp_fd);
	if ((*str) == NULL)
		exit_cub(parser->cb, NULL, 1);
}
