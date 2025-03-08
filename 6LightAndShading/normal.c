#include "../Includes/minirt.h"

t_vector	sphere_normal_at(t_point p)
{
	t_vector	normal;

	normal = sub_tuple(p, point(0, 0, 0));
	normal.w = 0;
	return (normalize(normal));
}

t_vector	plane_normal_at(t_point p)
{
	(void)p;
	return (vector(0, 1, 0));
}

t_vector	cylinder_normal_at(t_object o, t_point p)
{
	double	dist;

	dist = pow(p.x, 2) + pow(p.z, 2);
	if (dist < 1 && p.y >= o.maximum - EPSILON)
		return (vector(0, 1, 0));
	if (dist < 1 && p.y <= o.minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(p.x, 0, p.z));
}

t_vector	cone_normal_at(t_object o, t_point p)
{
	double		y;
	double		dist;
	double		max_radius;
	double		min_radius;
	t_vector	normal;

	dist = pow(p.x, 2) + pow(p.z, 2);
	max_radius = pow(o.maximum, 2);
	min_radius = pow(o.minimum, 2);
	if (dist < max_radius
		&& p.y >= o.maximum - EPSILON)
		normal = vector(0, 1, 0);
	else if (dist < min_radius
		&& p.y <= o.minimum + EPSILON)
		normal = vector(0, -1, 0);
	else
	{
		y = sqrt(dist);
		if (p.y > 0)
			y = -y;
		normal = vector(p.x, y, p.z);
	}
	return (normal);
}

t_vector	object_normal_at(t_object o, t_point p)
{
	if (o.type == SP)
		return (sphere_normal_at(p));
	else if (o.type == PL)
		return (plane_normal_at(p));
	else if (o.type == CY)
		return (cylinder_normal_at(o, p));
	else if (o.type == CN)
		return (cone_normal_at(o, p));
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
