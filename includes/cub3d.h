/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/06/28 14:16:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

typedef void	(*t_key_func)(int *val, int rate);

typedef struct s_keybind
{
	int			keycode;
	int			pressed;
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
	int			*fd;
}				t_map;

typedef struct s_cb
{
	void		*mlx;
	void		*win;
	t_map		*map;
	// t_key	*keys;
	t_img		img;
	// t_pers	pers;
}				t_cb;

void			draw_map(t_cb *cb, int map[10][10], int y_max, int x_max);

#endif