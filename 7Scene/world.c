#include "../Includes/minirt.h"

t_world	world(void)
{
	t_world w;

	my_bzero(&w, sizeof(t_world));
	return (w);
}

t_world	default_world(void)
{
	t_world		dworld;
	t_object	sphere1;
	t_object	sphere2;
	t_light		light;

	dworld = world();
	light = point_light(point(-10, 10, -10), color(1, 1, 1));
	add_light(&dworld.light, light);
	sphere1 = new_object(SP);
	sphere1.material.color = color(0.8, 1, 0.6);
	sphere1.material.diff = 0.7;
	sphere1.material.spec = 0.2;
	sphere2 = new_object(SP);
	set_transform(&sphere2, scaling(0.5, 0.5, 0.5));
	add_object(&dworld.object, sphere1);
	add_object(&dworld.object, sphere2);
	return (dworld);
}

void	add_light(t_light **l1, t_light l2)
{
	t_light	*new;
	t_light	*tmp;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_light));
	*new = l2;
	tmp = *l1;

	while(tmp && tmp->next)
		tmp = tmp->next;

	if(tmp)
		tmp->next = new;
	else
		*l1 = new;
}

void	add_object(t_object **obj1, t_object obj2)
{
	t_object	*new;
	t_object	*tmp;

	new = memcard(NULL, DEFAULT, MALLOC, sizeof(t_object));
	*new = obj2;
	tmp = *obj1;

	while(tmp && tmp->next)
		tmp = tmp->next;

	if(tmp)
		tmp->next = new;
	else
		*obj1 = new;
}

t_intersection	*intersect_world(t_world w, t_ray r)
{
	t_object	*tmp;
	t_intersection	*list;

	list = NULL;
	tmp = w.object;
	while(tmp)
	{
		intersect(&list, *tmp, r);
		tmp = tmp->next;
	}
	return (list);
}

t_comps	prepare_computations(t_intersection *inter, t_ray ray)
{
	t_comps	comps;

	comps.t = inter->t;
	comps.object = inter->object;
	comps.point = position(ray, comps.t);
	comps.eyev = inverse_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = inverse_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

bool	is_shadowed(t_world w, t_point p)
{
	t_vector	lightv;
	t_ray		shadow_ray;
	t_intersection	*inters;
	t_intersection	*result;

	lightv = sub_tuple(w.light->position, p);
	shadow_ray = ray(p, normalize(lightv));
	inters = intersect_world(w, shadow_ray);
	result = hit(inters);
	if (result != NULL && result->t > 0 && result->t < magnitude(lightv))
		return (true);
	return (false);
}

t_color	shade_hit(t_world w, t_comps comps)
{
	t_color color;
	bool	shadowed;

	shadowed = is_shadowed(w, comps.point);
	if (shadowed)
		color = mult_color(comps.object.material.color, comps.object.material.amb);
	else
		color = lighting(comps.object.material, *w.light, comps.point, comps.eyev, comps.normalv);
	return (color);
}

/*
t_color	color_at(t_world w, t_ray r)
{
	t_intersection *hit;
	t_comps	comps;

	hit = hit(intersect_world(w, r));
	if (!hit)
		return (color(0, 0, 0));
	comps = prepare_computations(hit, r);
	return (shade_hit(w, comps));
}
*/
