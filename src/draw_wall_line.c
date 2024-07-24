#include "../includes/cub3d.h"

int	get_pixel(t_img img, int x, int y)
{
	char	*dst;

	if (y >= img.height || x >= img.width || y < 0 || x < 0)
		return (-1);
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall_line(int x, t_vec2 wall_pos, t_cb *cb, double rot_offset)
{
	int		len;
	t_img	texture;
	int		i;
	double	y_scale;
	int		y_offest;
	int		color;
	int		texture_col;

	i = 0;
	//TODO: hacky fix, probly whould try to be more precise before (in get_next_wall)
	if (wall_pos.x == round(wall_pos.x))
	{
		if (clamp_rot(cb->player.rot + rot_offset) < PI)
			texture = cb->map.textures[1];
		else
			texture = cb->map.textures[3];
		texture_col = (wall_pos.y - floor(wall_pos.y)) * texture.width;
	}
	else if (round(wall_pos.y * 1000) == round(wall_pos.y) * 1000)
	{
		if (clamp_rot(cb->player.rot + rot_offset) <= 0.5 * PI
			|| clamp_rot(cb->player.rot + rot_offset) > 1.5 * PI)
			texture = cb->map.textures[0];
		else
			texture = cb->map.textures[2];
		texture_col = (wall_pos.x - floor(wall_pos.x)) * texture.width;
	}
	else
	{
		printf("error invalid wall: %.17g, %.17g\n", wall_pos.x, wall_pos.y);
		return ;
	}
	len = HEIGHT / distance(cb->player.pos, wall_pos);
	y_scale = (double)texture.height / len;
	y_offest = HEIGHT / 2 - len / 2;
	while (i < y_offest)
	{
		put_pixel(cb->img, x, i, cb->map.ceil_color);
		i++;
	}
	while (i < y_offest + len && i < HEIGHT)
	{
		color = get_pixel(texture, texture_col, (i - y_offest) * y_scale);
		put_pixel(cb->img, x, i, color);
		i++;
	}
	while (i < HEIGHT)
	{
		put_pixel(cb->img, x, i, cb->map.floor_color);
		i++;
	}
}
