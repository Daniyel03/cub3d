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



// if line found, read until count != i,
void	set_fd(t_parser *parser)
{
	close(parser->temp_fd);
	parser->temp_fd = open(parser->filename, O_RDONLY);
	while (++parser->i < parser->line_count)
		get_next_line(parser->temp_fd);
	parser->i = 0;
}

// reads until no empty line, returns 0 if fd is at its end
int	read_until_not_empty(t_parser *parser)
{
	parser->temp = get_next_line(parser->temp_fd);
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
	return 0;
}

