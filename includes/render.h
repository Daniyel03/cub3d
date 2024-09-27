#ifndef RENDERER_H
# define RENDERER_H

# include "cub3d.h"

typedef struct s_render_data
{
    t_cb    *cb;
	t_img	texture;
    int     distance;
    t_vec2  wall_hit;
    int     col;
    double  rot_offset;
}			t_render_data;

void		put_pixel(t_img img, int x, int y, int color);
double		distance(t_vec2 a, t_vec2 b);
void		draw_map(t_cb *cb);
void		draw_line(t_vec2 start, t_vec2 end, int color, t_img img);
void		draw_wall_line(t_render_data *data);
int			get_pixel(t_img img, int x, int y);

#endif