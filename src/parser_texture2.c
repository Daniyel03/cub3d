#include "../includes/cub3d.h"
#include "../includes/parser.h"



void	check_digit(t_parser *parser)
{
	iterate_until_space(&parser->temp);
	iterate_until_no_space(&parser->temp);
	parser->i = 0;
	while (!ft_isspace(parser->temp[parser->i]))
		parser->i++;
	if (!ft_isdigit(parser->file[0]) || !ft_isdigit(parser->file[parser->i
			- 1]))
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

void	numarray_to_hexadecimal(t_parser *parser)
{
	char	*table;
	char	*temp1;
	char	*temp2;
	int		temp;

	table = "0123456789abcdef";
	if (parser->i < 16)
	{
		temp1 = ft_substr(table, parser->i, 1);
		temp2 = ft_strjoin(parser->number, temp1);
		free(parser->number);
		free(temp1);
		parser->number = temp2;
		temp2 = NULL;
	}
	else
	{
		temp = parser->i;
		parser->i /= 16;
		numarray_to_hexadecimal(parser);
		parser->i = temp % 16;
		numarray_to_hexadecimal(parser);
	}
}

void	append_zero(t_parser *parser)
{
	char	*temp;

	temp = ft_strjoin(parser->number, "0");
	free(parser->number);
	parser->number = temp;
	temp = NULL;
}

void	set_digits(t_parser *parser)
{
	parser->number = ft_strdup("0x");
	parser->ptr = parser->numbers;
	while (*(char **)parser->ptr)
	{
		parser->i = ft_atoi(*(char **)parser->ptr);
		if (parser->i < 16)
			append_zero(parser);
		numarray_to_hexadecimal(parser);
		parser->ptr = (char **)parser->ptr + 1;
	}
}

void	rgb_to_hexadecimal(t_parser *parser)
{
	parser->numbers = ft_split(parser->file, ',');
	check_digit(parser);
	set_digits(parser);
	free(parser->file);
	parser->file = NULL;
}
