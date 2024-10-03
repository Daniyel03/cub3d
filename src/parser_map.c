#include "../includes/cub3d.h"
#include "../includes/parser.h"

void	set_player_rot(t_parser *parser, int *x, char *str)
{
	if (str[(*x)] == 'N')
		return (parser->cb->player.rot = PI, (void)0);
	if (str[(*x)] == 'S')
		return (parser->cb->player.rot = 0, (void)0);
	if (str[(*x)] == 'E')
		return (parser->cb->player.rot = PI * -0.25, (void)0);
	if (str[(*x)] == 'W')
		return (parser->cb->player.rot = PI * 1.5, (void)0);
}

void	iterate_line(t_parser *parser, int *x, char *str)
{
	while (str[(*x)] && str[(*x)] != '\n')
	{
		if (!(str[(*x)] == 'N' || str[(*x)] == 'W' || str[(*x)] == 'S'
				|| str[(*x)] == 'E') && str[(*x)] != '0' && str[(*x)] != '1'
			&& str[(*x)] != ' ' && str[(*x)] != '\0' && str[(*x)] != '\n')
			return (close(parser->temp_fd), free(str), exit_parser(parser,
					"invalid map input, only 0 and 1 allowed\n"));
		if (str[(*x)] == 'N' || str[(*x)] == 'W' || str[(*x)] == 'S'
			|| str[(*x)] == 'E')
		{
			if (parser->cb->player.pos.x != -1)
				return (close(parser->temp_fd), free(str), exit_parser(parser,
						"invalid map input, only one player position\n"));
			parser->cb->player.pos.x = (*x) + 0.5;
			parser->cb->player.pos.y = parser->cb->map.y + 0.5;
			set_player_rot(parser, x, str);
		}
		(*x)++;
	}
}

void	fill_lines(t_parser *parser)
{
	char	*str;
	char	*c;
	int		x;
	int		y;

	x = -1;
	y = 0;


	parser->i = parser->map_line;
	set_fd(parser);

	str = get_next_line(parser->temp_fd);
	while (y < parser->cb->map.y)
	{
		while (str[++x] && str[x] != '\n')
		{
			c = ft_substr(str, x, 1);
			if (!ft_strncmp(c, " ", 1))
				parser->cb->map.arr[y][x] = 2;
			else
				parser->cb->map.arr[y][x] = ft_atoi(c);
			free(c);
		}
		parser->cb->map.arr[y][x] = -1;
		y++;
		free(str);
		str = get_next_line(parser->temp_fd);
		x = -1;
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
		// parser->cb->map.arr[parser->cb->map.y] = NULL;
		if (!parser->cb->map.arr[parser->cb->map.y++])
			return (exit_cub(parser->cb, NULL));
		free(str);
		str = get_next_line(parser->temp_fd);
	}
	if (parser->cb->player.pos.x == -1)
		exit_parser(parser, 
		"No player position set, set it by placing either 'N', 'S', 'W', or 'E' within the map.\n");
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
	if (!parser->cb->map.arr)
		return (exit_parser(parser, NULL));
	if (close(parser->temp_fd) == -1)
		return (exit_parser(parser, NULL));
	validate_alloc_lines(parser);
	fill_lines(parser);
}
