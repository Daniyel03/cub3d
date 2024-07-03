#include "../includes/cub3d.h"

int	get_pixel(t_img img, int x, int y)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return (-1);
	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall_line(int x, t_vec2 wall_pos, t_cb *cb)
{
	int		len;
	t_img	texture;
	int		i;
	int		y_text;
	int		color;

	i = 0;
	if (wall_pos.x == round(wall_pos.x))
	{
		texture = cb->texture;
		y_text = (wall_pos.y - floor(wall_pos.y)) * texture.width;
	}
	else
		texture = cb->texture;
	len = HEIGHT / distance(cb->player.pos, wall_pos);
	if (len > HEIGHT)
		len = HEIGHT;
	while (i < len)
	{
		color = get_pixel(texture, 4, y_text);
		put_pixel(cb->img, x, HEIGHT / 2 - len / 2 + i, color);
		i++;
	}
}
