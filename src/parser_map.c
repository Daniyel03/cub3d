/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:30:01 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/09 14:07:40 by dscholz          ###   ########.fr       */
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
	free(str);
	str = NULL;
}

void	validate_alloc_lines_prep(t_parser *parser, char **str, int *x)
{
	parser->cb->map.y = 0;
	(*str) = NULL;
	(*x) = 0;
	parser->i = parser->map_line;
	set_fd(parser);
	(*str) = get_next_line(parser->temp_fd);
}

void	validate_alloc_lines(t_parser *parser)
{
	char	*str;
	int		x;

	validate_alloc_lines_prep(parser, &str, &x);
	while (str && empty_line(str))
	{
		x = 0;
		iterate_line(parser, &x, str);
		parser->cb->map.arr[parser->cb->map.y] = malloc(sizeof(int) * (x + 1));
		if (!parser->cb->map.arr[parser->cb->map.y++])
			return (exit_cub(parser->cb, NULL, 1));
		free(str);
		str = NULL;
		str = get_next_line(parser->temp_fd);
	}
	free(str);
	str = NULL;
	if (!parser->cb->map.y)
		return (exit_cub(parser->cb, "map is missing after textures\n", 1));
	if (parser->cb->player.pos.x == -1)
		exit_parser(parser, WRONG_PLAYER_POS);
}

void	after_map_check(t_parser *parser, char **temp)
{
	while ((*temp) && !empty_line((*temp)))
	{
		free((*temp));
		(*temp) = NULL;
		(*temp) = get_next_line(parser->temp_fd);
		if ((*temp) && empty_line((*temp)))
			exit_parser(parser, "no content after map allowed\n");
	}
}

void	alloc_array(t_parser *parser)
{
	int		count;
	char	*temp;

	alloc_array_prep(parser, &temp, &count);
	while (count++ != -1 && temp && empty_line(temp))
	{
		if (count > 500)
			exit_parser(parser, "map to big, y > 500\n");
		free(temp);
		temp = NULL;
		temp = get_next_line(parser->temp_fd);
	}
	after_map_check(parser, &temp);
	free(temp);
	temp = NULL;
	parser->cb->map.arr = malloc(sizeof(int *) * count);
	if (!parser->cb->map.arr || !count)
		return (exit_parser(parser, NULL));
	if (close(parser->temp_fd) == -1)
		return (exit_parser(parser, NULL));
	return (validate_alloc_lines(parser), fill_lines(parser), (void)0);
}
