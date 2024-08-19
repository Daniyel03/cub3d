#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

typedef struct s_valid_map
{
	// int last_graphic;
	// int						fd_textures;
	// int						fd_map;

}			t_valid_map;

typedef struct s_parser
{
	t_cb	*cb;
	char	*filename;
	int		graphics_count;
	// int		last_graphic;
	int		temp_fd;
	int		line_map;
}			t_parser;

void		validate_path(t_parser *parser, char **argv);
void		alloc_array(t_parser *parser);
int			flood_fill(t_parser *parser);
void		print_cord(t_cb *cb);
void		print_map(t_map map);
#endif