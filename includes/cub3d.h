/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 16:29:44 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "42get_next_line-master/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


# define WIDTH 1280
# define HEIGHT 720

typedef struct s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef void	(*t_key_func)(int *val, int rate);

typedef struct s_keybind
{
	int			keycode;
	int			pressed;
	int			*val;
	int			rate;
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
	int		fd;
	int		**arr;
	int		height;
	int		width;
}			t_map;

typedef struct s_cb
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_keybind	*keybinds;
	t_img		img;
	t_vec2		player_pos;
	// t_pers	pers;
}				t_cb;

void			draw_map(t_cb *cb, int map[10][10], int y_max, int x_max);
void			init_keybinds(t_cb *cb);
int				set_key(int keycode, int state, t_cb *cb);
void			setup_hooks(t_cb *cb);
void			apply_all_keys(t_cb *cb);

#endif