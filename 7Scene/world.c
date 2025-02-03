#include "../Includes/minirt.h"

//Capitulo 7

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
	add_object(&dworld.obj, sphere1);
	add_object(&dworld.obj, sphere2);
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

t_intersections	intersect_world(t_world w, t_ray r)
{
	
}
