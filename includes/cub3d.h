/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/10/05 12:01:18 by hannes           ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE -1
# define PI 3.1415926

// window
# define WIDTH 1080
# define HEIGHT 720

// rendering
# define FOV 1.570796327 // in radians
# define MAP_SCALE 200
# define MAP_X 20
# define MAP_Y 20
# define WHITE 0xffffff

// movement
# define WALK_SPEED 4
# define TURN_SPEED 3
# define JUMP_FORCE 25
# define GRAVITY 100

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

/**
 * @param textures: {NO, EA, SO, WE}
 */
typedef struct s_map
{
	char					*filename;
	int						**arr;
	char					**textures_arr;
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
	double					up_vel;
	double					z_pos;
}							t_player;

typedef void				(*t_key_func)(void *val, double rate, t_cb *cb);

typedef struct s_keybind
{
	int						keycode;
	t_key_func				func;
	double					*val;
	double					rate;
	int						pressed;
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
	int						show_map;
}							t_cb;

// x '2' y '1'
// x '1' y '1'
// x '3' y '1'

// init
int							init_mlx(t_cb *cb);
void						init_struct(t_cb *cb);
t_img						init_texture(char *filename, t_cb *cb);

// input handling
void						init_keybinds(t_cb *cb);
int							set_key(int keycode, int state, t_cb *cb);
void						setup_hooks(t_cb *cb);
void						apply_all_keys(t_cb *cb);
void						print_cord(t_cb *cb);

// rendering
void						draw_view(t_cb *cb);
void						draw_map(t_cb *cb);

// parser
void						parser(t_cb *cb, char **argv);
int							is_wall(t_cb *cb, int x, int y);
// parser_utils
int							empty(char *str);

// util
void						exit_cub(t_cb *cb, char *str, int status_code);
void						set_deltatime(t_cb *cb);
double						clamp_rot(double rot);
void						free_cords(t_cb *cb);
void						free_map(t_cb *cb);
void						free_ptr_arr(void **arr, int size);

int							is_wall(t_cb *cb, int x, int y);

// vector utils
t_vec2						get_dir_vec(double distance, double rot);
t_vec2						scale_vec(t_vec2 vec, double scale);
t_vec2						rotate(t_vec2 vec, double radians);
t_vec2						add_vec(t_vec2 a, t_vec2 b);
void						player_walk(t_cb *cb);
#endif