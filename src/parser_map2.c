/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:18:16 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/10 17:44:55 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	alloc_array_prep(t_parser *parser, char **temp, int *count)
{
	(*temp) = NULL;
	(*count) = 0;
	set_fd(parser);
	read_until_not_empty(parser);
	parser->map_line = parser->i;
	(*temp) = get_next_line(parser->temp_fd);
}

int	str_only_has_number(char *str)
{
	int	flag;

	flag = 0;
	while (*str && !(!ft_isspace(*str) && !ft_isdigit(*str)))
	{
		if (ft_isdigit(*str))
			flag = 1;
		str++;
	}
	if (*str == '\0' && flag == 1)
		return (1);
	return (0);
}
