#include "../Includes/minirt.h"

t_ray	ray(t_point p, t_vector v)
{
	t_ray	r;

	r.origin = p;
	r.direction = v;
	return (r);
}

t_point	position(t_ray r, double t)
{
	return (add_tuple(r.origin, mult_tuple(r.direction, t)));
}

//| JOGAR ESSA FUNÇÃO NA PASTA UTILS
double  bhaskara(t_object o, t_ray r)
{
	double		abc[3];
	t_vector	to_ray;

	to_ray = sub_tuple(r.origin, o.origin);
	abc[0] = dot(r.direction, r.direction); //| a
	abc[1] = 2 * dot(r.direction, to_ray);  //| b
	abc[2] = dot(to_ray, to_ray) - 1;       //| c
	return ((abc[1] * abc[1]) - (4 * abc[0] * abc[2]));
}

//| ESTÁ SÓ PARA A ESFERA, MAS DEVE SER ALTERADO PARA FUNCIONAR PARA TODOS OS OBJETOS DEPOIS
t_intersections intersect(t_object o, t_ray r)
{
	double		discriminant;
	double		ab[2];
	double		t[2];
	t_intersections	inter;

	inter.count = 0;
	discriminant = bhaskara(o, r);
	if (discriminant < 0)
		return (inter);
	ab[0] = dot(r.direction, r.direction);
	ab[1] = 2 * dot(r.direction, sub_tuple(r.origin, o.origin));
	t[0] = (-ab[1] - sqrt(discriminant)) / (2 * ab[0]);
	t[1] = (-ab[1] + sqrt(discriminant)) / (2 * ab[0]);
	//| ESFERA
	inter.count = 2;
	inter.intersection[0].t = t[0];
	inter.intersection[0].object = o;
	inter.intersection[1].t = t[1];
	inter.intersection[1].object = o;
	return (inter);
}

t_intersection  intersection(t_object o, double t)
{
	t_intersection	inter;

	inter.t = t;
	inter.object = o;
	return (inter);
}

t_intersections intersecitons(t_intersection i1, t_intersection i2)
{
	t_intersections	inter;

	inter.count = 2;
	inter.intersection[0] = i1;
	inter.intersection[1] = i2;
	return (inter);
}

t_intersection *hit(t_intersections inter)
{
	int				i;
	t_intersection	*hit;

	hit = NULL;
	i = 0;
	while (i < inter.count)
	{
		if (inter.intersection[i].t >= 0)
		{
			if (!hit || inter.intersection[i].t < hit->t)
				hit = &inter.intersection[i];
		}
		i++;
	}
	return (hit);
}
