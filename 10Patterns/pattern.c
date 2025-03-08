#include "../Includes/minirt.h"

t_pattern	new_pattern(t_pattern_type type, t_color a, t_color b)
{
	t_pattern	p;

	my_bzero(&p, sizeof(t_pattern));
	p.has_pattern = true;
	p.a = a;
	p.b = b;
	p.inversed = identity();
	p.transformed = identity();
	if (type == STRIPE)
		p.type = STRIPE;
	else if (type == GRADIENT)
		p.type = GRADIENT;
	else if (type == RING)
		type = RING;
	else if (type == CHECKER)
		p.type = CHECKER;
	else
		p.type = NO_TYPE;
	return (p);
}

t_color	stripe_at(t_pattern p, t_point pt)
{
	if ((int)floor(pt.x) % 2 == 0)
		return (p.a);
	return (p.b);
}

t_color	gradient_at(t_pattern p, t_point pt)
{
	double	fraction;
	t_color	distance;

	distance = sub_color(p.b, p.a);
	fraction = fmod(fabs(pt.x), 1);
	if (fmod(fabs(pt.x), 2) >= 1)
		fraction = 1 - fmod(fabs(pt.x), 1);
	return (add_color(mult_color(distance, fraction), p.a));
}

int	near_zero(double nb)
{
	return (nb < EPSILON && nb > -EPSILON);
}

t_color	ring_at(t_pattern p, t_point pt)
{
	double	discriminant;

	discriminant = floor(sqrt(pow(pt.x, 2) + pow(pt.z, 2)));
	if (near_zero(fmod(discriminant, 2)))
		return (p.a);
	return (p.b);
}

t_color	checker_at(t_pattern p, t_point pt)
{
	int	mod;
	int	sum;

	mod = 1;
	sum = (int)(pt.x + pt.y + pt.z);
	if (sum % 2 == 0)
		mod = 0;
	if (pt.x < 0)
		mod = !mod;
	if (pt.z < 0)
		mod = !mod;
	if (mod)
		return (p.a);
	return (p.b);
}

t_color	pattern_at_object(t_pattern pattern, t_object obj, t_point point)
{
	t_point	obj_point;
	t_point pat_point;

	obj_point = mult_matrix_tuple(obj.inversed, point);
	pat_point = mult_matrix_tuple(pattern.inversed, obj_point);
	if (pattern.type == STRIPE)
		return (stripe_at(pattern, pat_point));
	if (pattern.type == GRADIENT)
		return (gradient_at(pattern, pat_point));
	if (pattern.type == RING)
		return (ring_at(pattern, pat_point));
	if (pattern.type == CHECKER)
		return (checker_at(pattern, pat_point));
	return (pattern.a);
}

void	set_pattern_transform(t_pattern *p, t_matrix transform)
{
	p->transformed = transform;
	p->inversed = inverse(transform);
}
