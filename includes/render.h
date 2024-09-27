#ifndef RENDERER_H
# define RENDERER_H

# include "cub3d.h"
void	put_pixel(t_img img, int x, int y, int color);
double	distance(t_vec2 a, t_vec2 b);
void	draw_map(t_cb *cb);
void	draw_line(t_vec2 start, t_vec2 end, int color, t_img img);
void	draw_wall_line(int x, t_vec2 wall_pos, t_cb *cb, double rot_offset);
int		get_pixel(t_img img, int x, int y);

#endif