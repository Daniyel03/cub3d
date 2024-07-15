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

	(void)rot_offset;
	i = 0;
	if (wall_pos.x == round(wall_pos.x))
	{
		texture = cb->textures[0];
		texture_col = (wall_pos.y - floor(wall_pos.y)) * texture.width;
	}
	else
	{
		texture = cb->textures[1];
		texture_col = (wall_pos.x - floor(wall_pos.x)) * texture.width;
	}

	len = HEIGHT / (distance(cb->player.pos, wall_pos) * cos(rot_offset));
	y_scale = (double)texture.height / len;
	y_offest = HEIGHT / 2 - len / 2;
	if (len > HEIGHT)
	{
		i += (len - HEIGHT) / 2;
		len -= i;
	}
	while (i < len)
	{
		color = get_pixel(texture, texture_col, i * y_scale);
		put_pixel(cb->img, x, y_offest + i, color);
		i++;
	}
}
