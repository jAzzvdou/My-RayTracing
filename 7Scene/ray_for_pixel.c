#include "../Includes/minirt.h"

t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	double		d[4];
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	d[0] = (px + 0.5) * c.pixel_size;
	d[1] = (py + 0.5) * c.pixel_size;
	d[2] = c.half_width - d[0];
	d[3] = c.half_height - d[1];
	pixel = mult_matrix_tuple(c.inverse, point(d[2], d[3], -1)); // trocar o inverse(c.transform) para apenas c.inverse
	origin = mult_matrix_tuple(c.inverse, point(0, 0, 0)); // trocar o inverse(c.transform) para apenas c.inverse
	direction = normalize(sub_tuple(pixel, origin));
	return (ray(origin, direction));
}
