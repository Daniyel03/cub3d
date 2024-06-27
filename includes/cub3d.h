/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:12 by hrother           #+#    #+#             */
/*   Updated: 2024/06/27 18:16:52 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct t_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_map
{
	int		*fd;
}			t_map;

typedef struct s_cb
{
	void	*mlx;
	void	*win;
	t_map	*map;
	// t_key	*keys;
	t_img	img;
	// t_pers	pers;
} t_cb;

#endif