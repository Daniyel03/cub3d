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
void		alloc_array(t_parser *parser);
int			flood_fill(t_cb *cb);
void		print_cord(t_cb *cb);
void		print_map(t_map map);

//utils
int	ft_isspace(char c);
int	empty_line(char *str);
void	set_fd(t_parser *parser);
int	read_until_not_empty(t_parser *parser);
void	iterate_until_no_space(char **str);
void	iterate_until_space(char **str);
int	str_is_number(char *str);
void	exit_parser(t_parser *parser, char *errormessage);
void	print_textures(t_parser *parser);

#endif