#include "cub3d.h"

double distance(t_vec2 a, t_vec2 b)
{
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

t_vec2	get_dir_vec(double distance, double rot)
{
	t_vec2	ret;

	ret.x = distance * sin(rot);
	ret.y = distance * cos(rot);
	return (ret);
}

t_vec2	scale_vec(t_vec2 vec, double scale)
{
	vec.x *= scale;
	vec.y *= scale;
	return (vec);
}

t_vec2 rotate(t_vec2 vec, double radians)
{
	t_vec2 ret;

	ret.x = vec.x * cos(radians) - vec.y * sin(radians);
	ret.y = vec.x * sin(radians) + vec.y * cos(radians);
	return (ret);
}
