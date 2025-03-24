#include "../Includes/minirt.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

t_point	point(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1.0;
	return (p);
}
