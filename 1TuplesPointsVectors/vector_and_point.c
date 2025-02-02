#include "../Includes/minirt.h"

t_point	point(double x, double y, double z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1.0;
	return (p);
}

t_vector	vector(double x, double y, double z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0.0;
	return (v);
}

t_vector	normalize(t_vector v)
{
	double len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}

t_vector	cross(t_vector a, t_vector b)
{
	t_vector v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

double	magnitude(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
