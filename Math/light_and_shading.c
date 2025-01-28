#include "../Includes/minirt.h"

t_vector	sphere_normal_at(t_point p)
{
	t_vector	normal;

	normal = sub_tuple(p, point(0, 0, 0));
	normal.w = 0;
	return (normalize(normal));
}

t_vector	object_normal_at(t_object o, t_point p)
{
	if (o.type == SP)
		return (sphere_normal_at(p));
	return ((t_vector){0, 0, 0, 0});
}

t_vector	normal_at(t_object o, t_point p)
{
	t_point		obj_point;
	t_point		obj_normal;
	t_vector	world_normal;

	obj_point = mult_matrix_tuple(o.inversed, p);
	obj_normal = object_normal_at(o, obj_point);
	world_normal = mult_matrix_tuple(o.transposed, obj_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_vector	reflect(t_vector in, t_vector normal)
{
	return (sub_tuple(in, mult_tuple(normal, 2 * dot(in, normal))));
}
