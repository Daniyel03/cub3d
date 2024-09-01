#include "../includes/cub3d.h"
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

// if line found, read until count != i,
void	set_fd(t_parser *parser)
{
	int i;

	i = 0;
	close(parser->temp_fd);
	parser->temp_fd = open(parser->filename, O_RDONLY);
	while (++i < parser->line_count)
		get_next_line(parser->temp_fd);
}

int	read_until_not_empty(t_parser *parser)
{
	char *temp;

	temp = NULL;
	temp = get_next_line(parser->temp_fd);
	if (parser->line_count == 0)
		parser->line_count = 1;
	while (temp)
	{
		if (temp == NULL)
			return (free(temp), 0);
		if (empty_line(temp))
			return (free(temp), set_fd(parser), 1);
		free(temp);
		temp = get_next_line(parser->temp_fd);
		parser->line_count++;
	}
	return 0;
}

