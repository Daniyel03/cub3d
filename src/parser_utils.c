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

int	str_is_number(char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return 1;
	return 0;
}

// if line found, read until count != i,
void	set_fd(t_parser *parser)
{
	parser->i = 0;
	close(parser->temp_fd);
	parser->temp_fd = open(parser->filename, O_RDONLY);
	while (++parser->i < parser->line_count)
	{
		parser->str = get_next_line(parser->temp_fd);
		free(parser->str);
		parser->str = NULL;
	}
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

void	print_textures(t_parser *parser)
{
	printf("0: %s\n", parser->textures[0]);
	printf("1: %s\n", parser->textures[1]);
	printf("2: %s\n", parser->textures[2]);
	printf("3: %s\n", parser->textures[3]);
	printf("4: %s\n", parser->textures[4]);
	printf("5: %s\n", parser->textures[5]);

}

void	exit_parser(t_parser *parser, char *errormessage)
{
	print_textures(parser);
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
	free(parser->textures[0]);
	parser->textures[0] = NULL;
	free(parser->textures[1]);
	parser->textures[1] = NULL;
	free(parser->textures[2]);
	parser->textures[2] = NULL;
	free(parser->textures[3]);
	parser->textures[3] = NULL;
	free(parser->textures[4]);
	parser->textures[4] = NULL;
	free(parser->textures[5]);
	parser->textures[5] = NULL;
	free(parser->textures);
	parser->textures = NULL;
	if (parser->str)
		free(parser->str);
	if (parser->file)
		free(parser->file);
	// if (parser->number)
	// 	free(parser->number);

	if (parser->cb->map.arr)
	{
		if (parser->cb->map.y)
			while (parser->cb->map.y)
				free(parser->cb->map.arr[--parser->cb->map.y]);
		free(parser->cb->map.arr);
	}
	ft_bzero(parser, sizeof(&parser));


	// exit_cub(parser->cb, "exit");
	if (errormessage)
		ft_putstr_fd(errormessage, 2);
	exit(0);
}