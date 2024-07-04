#include "../includes/cub3d.h"

int	get_pixel(t_img img, int x, int y)
{
	char	*dst;

	if (y >= img.height || x >= img.width || y < 0 || x < 0)
		return (-1);
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall_line(int x, t_vec2 wall_pos, t_cb *cb)
{
	int		len;
	t_img	texture;
	int		i;
	int		texture_col;
	int		color;
	int		texture_row;

	i = 0;
	if (wall_pos.x == round(wall_pos.x))
	{
		texture = cb->texture;
		texture_col = (wall_pos.y - floor(wall_pos.y)) * texture.width;
	}
	else
	{
		texture = cb->texture; // use different texture here
		texture_col = (wall_pos.x - floor(wall_pos.x)) * texture.width;
	}
	len = HEIGHT / distance(cb->player.pos, wall_pos);
	if (len > HEIGHT)
		len = HEIGHT;
	while (i < len)
	{
		texture_row = ((double)i / len) * texture.height;
		color = get_pixel(texture, texture_col, texture_row);
		put_pixel(cb->img, x, HEIGHT / 2 - len / 2 + i, color);
		i++;
	}
}
