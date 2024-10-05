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

void	numarray_to_hexadecimal_prep(int *temp, char **table, char **temp1, char **temp2)
{
	(*table) = NULL;
	(*temp1) = NULL;
	(*temp2) = NULL;
	(*temp) = 0;
}

void	numarray_to_hexadecimal(t_parser *parser)
{
	char	*table;
	char	*temp1;
	char	*temp2;
	int		temp;


	numarray_to_hexadecimal_prep(&temp, &table, &temp1, &temp2);
	table = "0123456789abcdef";
	if (parser->i < 16)
	{
		temp1 = ft_substr(table, parser->i, 1);
		if (temp1 == NULL)
			exit_parser(parser, NULL);
		temp2 = ft_strjoin(parser->number, temp1);
		if (temp2 == NULL)
			exit_parser(parser, NULL);

		return (free(parser->number), parser->number = NULL, free(temp1), temp1 = NULL, parser->number = temp2, temp2 = NULL, (void)0);
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
	if (temp == NULL)
		exit_parser(parser, NULL);
	free(parser->number);
	parser->number = temp;
	temp = NULL;
}

void	set_digits(t_parser *parser)
{
	parser->number = ft_strdup("0x");
	if (parser->number == NULL)
		exit_parser(parser, NULL);
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
	if (parser->numbers == NULL)
		exit_parser(parser, NULL);
	check_digit(parser);
	set_digits(parser);
	free(parser->file);
	parser->file = NULL;
}
