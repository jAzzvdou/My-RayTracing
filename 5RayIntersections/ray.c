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

int	count_intersection(t_intersection *list)
{
	int				count;
	t_intersection	*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
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
	double		discriminant;
	double		ab[2];
	double		t[2];

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
	double	abc[3]; //| 0:a, 1:b, 2:c
	double	discriminant;

	intersect_caps(list, o, r);
	abc[0] = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (near_zero(abc[0]))
		return ;
	abc[1] = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	abc[2] = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1;
	discriminant = pow(abc[1], 2) - (4 * abc[0] * abc[2]);
	if (discriminant < 0)
		return ;
	double t0 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	double t1 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t0 > t1)
		swap(&t0, &t1);
	double y0 = r.origin.y + t0 * r.direction.y;
	if (o.minimum < y0 && y0 < o.maximum)
		add_intersection(list, intersection(o, t0));
	double y1 = r.origin.y + t1 * r.direction.y;
	if (o.minimum < y1 && y1 < o.maximum)
		add_intersection(list, intersection(o, t1));
}

void	intersect_cone(t_intersection **list, t_object o, t_ray r)
{
	double abc[3]; //| 0:a, 1:b, 2:c
	double discriminant;
	double t0t1[2];
	double y0y1[2];

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
	//| Adicionar outros depois
}

t_intersection	*hit(t_intersection *inter)
{
	t_intersection	*tmp;

	tmp = inter;
	while (tmp && tmp->t < 0)
		tmp = tmp->next;
	return (tmp);
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

t_object	fill_plane(t_object obj)
{
	obj.type = PL;
	obj.origin = point(0, 0, 0);
	return (obj);
}

t_object	fill_cylinder(t_object obj)
{
	obj.type = CY;
	obj.origin = point(0, 0, 0);
	obj.radius = 1;
	obj.minimum = -INFINITY;
	obj.maximum = INFINITY;
	obj.closed = false;
	return (obj);
}

t_object	fill_cone(t_object obj)
{
	obj.type = CN;
	obj.origin = point(0, 0, 0);
	obj.radius = 1;
	obj.minimum = -INFINITY;
	obj.maximum = INFINITY;
	obj.closed = false;
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
	else if (type == PL)
		return (fill_plane(obj));
	else if (type == CY)
		return (fill_cylinder(obj));
	else if (type == CN)
		return (fill_cone(obj));
	obj.type = NONE;
	return (obj);
}
