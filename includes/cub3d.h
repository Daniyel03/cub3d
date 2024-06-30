/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/06/30 11:47:56 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define MAP_SCALE 50

# define SUCCESS 0
# define FAILURE -1

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef void	(*t_key_func)(double *val, double rate);

typedef struct s_valid_cords
{
	int			x;
	int			y;
	struct s_valid_cords	*next;
}				t_valid_cords;


typedef struct s_keybind
{
	int			keycode;
	int			pressed;
	double		*val;
	double		rate;
	t_key_func	func;
}				t_keybind;

typedef struct t_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_map
{
	char		*filename;
	int			**arr;
	int			y;
	int			width;
	int			height;
}				t_map;

typedef struct s_cb
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_keybind	*keybinds;
	t_img		img;
	t_vec2		player_pos;
	t_valid_cords *cords;
	// t_pers	pers;
}				t_cb;

// input handling
void			init_keybinds(t_cb *cb);
int				set_key(int keycode, int state, t_cb *cb);
void			setup_hooks(t_cb *cb);
void			apply_all_keys(t_cb *cb);

// rendering
double			distance(t_vec2 a, t_vec2 b);
void			draw_map(t_cb *cb);

// parser
void			validate_path(t_cb *cb, char **argv);
void			alloc_array(t_cb *cb);
int				flood_fill(t_cb *cb);
void	print_cord(t_cb *cb);

// util
void			exit_cub(t_cb *cb, char *str);
void			print_map(t_map map);

#endif