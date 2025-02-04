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

t_intersection	intersection(t_object o, double t)
{
	t_intersection	inter;

	inter.object = o;
	inter.t = t;
	inter.next = NULL;
	return (inter);
}

void	add_intersection(t_intersection **list, t_intersection inter)
{
	t_intersection	*new;
	t_intersection	*tmp;
	t_intersection	*prev;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_intersection));
	*new = inter;
	prev = NULL;
	tmp = *list;
	while (tmp && tmp->t < inter.t)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
	{
		prev->next = new;
		new->next = tmp;
		return ;
	}
	new->next = *list;
	*list = new;
}

void	intersect_sphere(t_intersection **list, t_object o, t_ray r)
{
	double		t1;
	double		t2;
	double		discriminant;

	discriminant = bhaskara(o, r);
	if (discriminant < 0)
		return ;
	t1 = (-dot(r.direction, sub_tuple(r.origin, o.origin)) + sqrt(discriminant)) / (2 * dot(r.direction, r.direction));
	t2 = (-dot(r.direction, sub_tuple(r.origin, o.origin)) - sqrt(discriminant)) / (2 * dot(r.direction, r.direction));
	add_intersection(list, intersection(o, t1));
	add_intersection(list, intersection(o, t2));
}


//| Testes
t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray	new;

	new.origin = mult_matrix_tuple(m, r.origin);
	new.direction = mult_matrix_tuple(m, r.direction);
	return (new);
}

void	intersect(t_intersection **list, t_object o, t_ray ray)
{
	//t_ray	r;

	//r = ray_transform(ray, o.inversed);
	if (o.type == SP)
		intersect_sphere(list, o, ray);
	//| Adicionar outros depois
}

t_intersection	hit(t_intersection *inter)
{
	t_intersection	hit;
	t_intersection	*tmp;

	my_bzero(&hit, sizeof(t_intersection));
	hit.t = -1;
	tmp = inter;
	while (tmp)
	{
		if (tmp->t > 0 && (hit.t < 0 || tmp->t < hit.t))
			hit = *tmp;
		tmp = tmp->next;
	}
	return (hit);
}

void	set_transform(t_object *o, t_matrix m)
{
	o->transformed = m;
	o->inversed = inverse(m);
	o->transposed = transpose(o->inversed);
}

t_object	fill_sphere(t_object obj)
{
	obj.type = SP;
	obj.origin = point(0, 0, 0);
	obj.radius = 1;
	return (obj);
}

t_object	new_object(t_type type)
{
	static int	id;
	t_object	obj;

	my_bzero(&obj, sizeof(t_object));
	obj.id = id++;
	obj.transformed = identity();
	obj.inversed = identity();
	obj.transposed = identity();
	obj.material = material();
	obj.next = NULL;
	if (type == SP)
		return (fill_sphere(obj));
	/*else if (type == PL)
		fill_plane(&obj);
	else if (type == CY)
		fill_cylinder(&obj);*/
	obj.type = NONE;
	return (obj);
}
