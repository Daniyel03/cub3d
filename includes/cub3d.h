/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/08/19 06:11:18 by dscholz          ###   ########.fr       */
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
// # include <../minilibx-linux/mlx_int.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
// # include "parser.h"

# define WIDTH 1080
# define HEIGHT 720
# define FOV 3.141 / 2 // in radians
# define PI 3.1415926
# define Y_SCALE 500
# define MAP_SCALE 50

# define SUCCESS 0
# define FAILURE -1

# define WHITE 0xffffff
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define SHADE1 0xdbb11a
# define SHADE2 0xb89723

typedef struct s_cb			t_cb;

typedef struct s_vec2
{
	double					x;
	double					y;
}							t_vec2;

typedef struct s_valid_cords
{
	int						x;
	int						y;
	struct s_valid_cords	*next;
}							t_valid_cords;

typedef struct s_line_data
{
	int						dx;
	int						dy;
	int						step_x;
	int						step_y;
	int						swap;
	int						x;
	int						y;
	int						error;
}							t_line_data;

typedef struct t_img
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						width;
	int						height;
}							t_img;

//textures: {NO, EA, SO, WE}
typedef struct s_map
{
	char						**arr;
	char 	**textures_arr;
	int						y;
	int						width;
	int						height;
	t_img					textures[4];
	int						ceil_color;
	int						floor_color;
}							t_map;

/**
 * @param rot: player rotation in radians
 */
typedef struct s_player
{
	t_vec2					input;
	t_vec2					pos;
	double					rot;
}							t_player;

typedef void				(*t_key_func)(void *cb, double rate);

typedef struct s_keybind
{
	int						keycode;
	int						pressed;
	double					*val;
	double					rate;
	t_key_func				func;
}							t_keybind;

/**
 * @param deltatime: time between frames in seconds
 */
typedef struct s_cb
{
	void					*mlx;
	void					*win;
	t_map					map;
	t_keybind				*keybinds;
	t_img					img;
	t_player				player;
	t_valid_cords			*cords;
	double					deltatime;
}							t_cb;

// input handling
void						init_keybinds(t_cb *cb);
int							set_key(int keycode, int state, t_cb *cb);
void						setup_hooks(t_cb *cb);
void						apply_all_keys(t_cb *cb);

// rendering
void						put_pixel(t_img img, int x, int y, int color);
double						distance(t_vec2 a, t_vec2 b);
void						draw_map(t_cb *cb);
void						draw_line(t_vec2 start, t_vec2 end, int color,
								t_img img);
void						draw_view(t_cb *cb);
void						draw_wall_line(int x, t_vec2 wall_pos, t_cb *cb,
								double rot_offset);
int							get_pixel(t_img img, int x, int y);

// parser
void	parser(t_cb *cb, char **argv);

//parser_utils
int	empty(char *str);

// util
void						exit_cub(t_cb *cb, char *str);
long						get_time_ms(void);
double						clamp_rot(double rot);

// vector utils
t_vec2						get_dir_vec(double distance, double rot);
t_vec2						scale_vec(t_vec2 vec, double scale);
t_vec2						rotate(t_vec2 vec, double radians);
t_vec2						add_vec(t_vec2 a, t_vec2 b);
void						player_walk(t_cb *cb);
#endif