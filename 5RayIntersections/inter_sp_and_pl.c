#include "../Includes/minirt.h"

void	intersect_sphere(t_intersection **list, t_object o, t_ray r)
{
	double	discriminant;
	double	ab[2];
	double	t[2];

	discriminant = bhaskara(o, r);
	if (discriminant < 0)
		return ;
	ab[0] = dot(r.direction, r.direction);
	ab[1] = 2 * dot(r.direction, sub_tuple(r.origin, o.origin));
	t[0] = (-ab[1] - sqrt(discriminant)) / (2 * ab[0]);
	t[1] = (-ab[1] + sqrt(discriminant)) / (2 * ab[0]);
	add_intersection(list, intersection(o, t[0]));
	add_intersection(list, intersection(o, t[1]));
}

void	intersect_plane(t_intersection **list, t_object o, t_ray r)
{
	double	t;

	if (fabs(r.direction.y) < EPSILON)
		return ;
	t = -r.origin.y / r.direction.y;
	if (fabs(t) > EPSILON)
		add_intersection(list, intersection(o, t));
}

t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray	new;

	new.origin = mult_matrix_tuple(m, r.origin);
	new.direction = mult_matrix_tuple(m, r.direction);
	return (new);
}

void	intersect(t_intersection **list, t_object o, t_ray ray)
{
	t_ray	r;

	r = ray_transform(ray, o.inversed);
	if (o.type == SP)
		intersect_sphere(list, o, r);
	else if (o.type == PL)
		intersect_plane(list, o, r);
	else if (o.type == CY)
		intersect_cylinder(list, o, r);
	else if (o.type == CN)
		intersect_cone(list, o, r);
}
