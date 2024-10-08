/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:18:16 by dscholz           #+#    #+#             */
/*   Updated: 2024/10/08 16:18:17 by dscholz          ###   ########.fr       */
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
