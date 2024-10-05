/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:30:01 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/05 14:32:14 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

void	fill_lines(t_parser *parser)
{
	char	*str;
	char	*c;
	int		x;
	int		y;

	fill_line_prep(parser, &str, &y, &x);
	while (y < parser->cb->map.y)
	{
		if (str == NULL)
			exit_cub(parser->cb, NULL, 1);
		while (str[++x] && str[x] != '\n')
		{
			c = ft_substr(str, x, 1);
			if (c == NULL)
				(free(str), exit_cub(parser->cb, "malloc fail\n", 1));
			if (!ft_strncmp(c, " ", 1))
				parser->cb->map.arr[y][x] = 2;
			else
				parser->cb->map.arr[y][x] = ft_atoi(c);
			free(c);
		}
		next_line(parser, &str, &y, &x);
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
			return (exit_cub(parser->cb, NULL, 1));
		free(str);
		str = get_next_line(parser->temp_fd);
	}
	if (!parser->cb->map.y)
		return (exit_cub(parser->cb, NULL, 1));
	if (parser->cb->player.pos.x == -1)
		exit_parser(parser, WRONG_PLAYER_POS);
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
	if (!parser->cb->map.arr || !count)
		return (exit_parser(parser, NULL));
	if (close(parser->temp_fd) == -1)
		return (exit_parser(parser, NULL));
	validate_alloc_lines(parser);
	fill_lines(parser);
}
