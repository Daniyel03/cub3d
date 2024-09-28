#include "render.h"

int	get_pixel(t_img img, int x, int y)
{
	char	*dst;

	if (y >= img.height || x >= img.width || y < 0 || x < 0)
		return (-1);
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall_line(t_render_data *data)
{
	int		len;
	t_img	texture;
	int		i;
	double	y_scale;
	int		y_offest;
	int		color;
	int		texture_col;

	i = 0;
	texture = data->cb->map.textures[1];
	// TODO: hacky fix, probly whould try to be more precise before (in get_next_wall)
	if (data->wall_hit.x == round(data->wall_hit.x) || data->wall_hit.x < 1)
	{
	/*
		if (clamp_rot(data->cb->player.rot + data->rot_offset) < PI)
			texture = data->cb->map.textures[1];
		else
			texture = data->cb->map.textures[3];
	*/
		texture_col = (data->wall_hit.y - floor(data->wall_hit.y)) * texture.width;
	}
	else if (round(data->wall_hit.y * 1000) == round(data->wall_hit.y) * 1000)
	{
	/*
		if (clamp_rot(data->cb->player.rot + data->rot_offset) <= 0.5 * PI
			|| clamp_rot(data->cb->player.rot + data->rot_offset) > 1.5 * PI)
			texture = data->cb->map.textures[0];
		else
			texture = data->cb->map.textures[2];
	*/
		texture_col = (data->wall_hit.x - floor(data->wall_hit.x)) * texture.width;
	}
	else
	{
		printf("error invalid wall: %.17g, %.17g\n", data->wall_hit.x, data->wall_hit.y);
		return ;
	}
	len = HEIGHT / (distance(data->cb->player.pos, data->wall_hit) * cos(data->rot_offset));
	y_scale = (double)texture.height / len;
	y_offest = HEIGHT / 2 - len / 2;
	while (i < y_offest)
	{
		put_pixel(data->cb->img, data->col, i, data->cb->map.ceil_color);
		i++;
	}
	while (i < y_offest + len && i < HEIGHT)
	{
		color = get_pixel(texture, texture_col, (i - y_offest) * y_scale);
		put_pixel(data->cb->img, data->col, i, color);
		i++;
	}
	while (i < HEIGHT)
	{
		put_pixel(data->cb->img, data->col, i, data->cb->map.floor_color);
		i++;
	}
}
