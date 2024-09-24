#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include "../libft/libft.h"

typedef struct s_valid_map
{
	// int last_graphic;
	// int						fd_textures;
	// int						fd_map;

}			t_valid_map;

typedef struct s_parser
{
	t_cb	*cb;
	char	**numbers;
	char	*filename;
	char 	*temp;
	char 	*str;
	char	*file;
	char	*number;
	int		i;
	int		map_line;
	int		line_count;
	int		temp_fd;
	int		line_map;
	void	*ptr;
}			t_parser;

void		validate_path(t_parser *parser, char **argv);
int			flood_fill(t_cb *cb);
void		print_cord(t_cb *cb);
void		print_map(t_map map);
//parser
void	get_filename(t_parser *parser, char **argv);
int	check_direction(t_parser *parser);
void	check_commas(t_parser *parser);
void	validate_input(t_parser *parser, char **argv);
void	parser(t_cb *cb, char **argv);


//parser_utils1
int	ft_isspace(char c);
int	empty_line(char *str);
void	iterate_until_no_space(char **str);
void	iterate_until_space(char **str);
void	is_dir_set(t_parser *parser);

//parser_utils2
int	str_is_number(char *str);
void	set_fd(t_parser *parser);
int	read_until_not_empty(t_parser *parser);
void	print_textures(t_parser *parser);
void	exit_parser(t_parser *parser, char *errormessage);

//parser_map
void	set_player_rot(t_parser *parser, int *x, char *str);
void	iterate_line(t_parser *parser, int *x, char *str);
void	fill_lines(t_parser *parser);
void	validate_alloc_lines(t_parser *parser);
void	alloc_array(t_parser *parser);

//parser_textures_1
void	set_texture(t_parser *parser);
void	test_texture_path(t_parser *parser);
void	check_texture(t_parser *parser);
void	validate_textures(t_parser *parser);
void	set_texture_reset(t_parser *parser);

//parser_textures_2
void	check_digit(t_parser *parser);
void	numarray_to_hexadecimal(t_parser *parser);
void	append_zero(t_parser *parser);
void	set_digits(t_parser *parser);
void	rgb_to_hexadecimal(t_parser *parser);

#endif