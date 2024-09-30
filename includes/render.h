/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:26:00 by hrother           #+#    #+#             */
/*   Updated: 2024/09/30 12:26:47 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

typedef struct s_render_data
{
	t_cb	*cb;
	t_img	texture;
	t_vec2	wall_hit;
	int		cam_col;
	int		texture_col;
	double	rot_offset;
}			t_render_data;

void		put_pixel(t_img img, int x, int y, int color);
double		distance(t_vec2 a, t_vec2 b);
void		draw_wall_line(t_render_data *data);
int			get_pixel(t_img img, int x, int y);

#endif