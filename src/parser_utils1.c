/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:30:50 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/05 13:31:31 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/cub3d.h"
#include "../includes/parser.h"
#include <fcntl.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

int	empty_line(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
			return (1);
	}
	return (0);
}

void	iterate_until_no_space(char **str)
{
	while (ft_isspace(*(*str)) && *(*str) != '\0')
		(*str)++;
}

void	iterate_until_space(char **str)
{
	while (!ft_isspace(*(*str)) && *(*str) != '\0')
		(*str)++;
}

void	is_dir_set(t_parser *parser)
{
	if (parser->cb->map.textures_arr[parser->i])
		return (exit_parser(parser,
				"direction already set / exists more than once\n"));
}
