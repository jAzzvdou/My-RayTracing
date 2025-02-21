#include "../Includes/minirt.h"

t_color	reflected_color(t_world w, t_comps comps, int remaining)
{
	t_ray	reflect_ray;
	t_color	c;

	if (comps.object.material.reflective == 0 || remaining <= 0)
		return (color(0, 0, 0));
	reflect_ray = ray(comps.over_point, comps.reflectv);
	c = color_at(w, reflect_ray, remaining - 1);
	return (mult_color(c, comps.object.material.reflective));
}
