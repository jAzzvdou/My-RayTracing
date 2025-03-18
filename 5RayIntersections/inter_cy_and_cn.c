#include "../Includes/minirt.h"

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	check_cap(t_ray r, double t, double cap_y_pos)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return ((pow(x, 2) + pow(z, 2)) <= pow(cap_y_pos, 2));
}

void	intersect_caps(t_intersection **list, t_object o, t_ray r)
{
	double	t;

	if (o.closed == false || near_zero(r.direction.y))
		return ;
	t = (o.minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t, o.minimum))
		add_intersection(list, intersection(o, t));
	t = (o.maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t, o.maximum))
		add_intersection(list, intersection(o, t));
}

void	intersect_cylinder(t_intersection **list, t_object o, t_ray r)
{
	double	abc[3];
	double	discriminant;
	double	t01[2];
	double	y01[2];

	intersect_caps(list, o, r);
	abc[0] = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (near_zero(abc[0]))
		return ;
	abc[1] = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	abc[2] = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1;
	discriminant = pow(abc[1], 2) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return ;
	t01[0] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	t01[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t01[0] > t01[1])
		swap(&t01[0], &t01[1]);
	y01[0] = r.origin.y + t01[0] * r.direction.y;
	if (o.minimum < y01[0] && y01[0] < o.maximum)
		add_intersection(list, intersection(o, t01[0]));
	y01[1] = r.origin.y + t01[1] * r.direction.y;
	if (o.minimum < y01[1] && y01[1] < o.maximum)
		add_intersection(list, intersection(o, t01[1]));
}

void	intersect_cone(t_intersection **list, t_object o, t_ray r)
{
	double	abc[3];
	double	discriminant;
	double	t0t1[2];
	double	y0y1[2];

	intersect_caps(list, o, r);
	abc[0] = pow(r.direction.x, 2) - pow(r.direction.y, 2) + pow(r.direction.z, 2);
	abc[1] = 2 * (r.origin.x * r.direction.x - r.origin.y * r.direction.y + r.origin.z * r.direction.z);
	abc[2] = pow(r.origin.x, 2) - pow(r.origin.y, 2) + pow(r.origin.z, 2);

	if (near_zero(abc[0]))
		return;
	discriminant = pow(abc[1], 2) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return;
	t0t1[0] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	t0t1[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t0t1[0] > t0t1[1])
		swap(&t0t1[0], &t0t1[1]);
	y0y1[0] = r.origin.y + t0t1[0] * r.direction.y;
	y0y1[1] = r.origin.y + t0t1[1] * r.direction.y;
	if (o.minimum < y0y1[0] && y0y1[0] < o.maximum)
		add_intersection(list, intersection(o, t0t1[0]));
	if (o.minimum < y0y1[1] && y0y1[1] < o.maximum)
		add_intersection(list, intersection(o, t0t1[1]));
}
