#include "../Includes/minirt.h"

t_color	reflected_color(t_world w, t_comps comps, int remaining)
{
	t_ray	reflect_ray;
	t_color	c;

	if (comps.object.material.reflective == 0 || remaining <= 0)
		return (color(0, 0, 0));
	reflect_ray = ray(comps.over_point, comps.reflectv);
	c = color_at(w, reflect_ray, remaining - 1);
	return (mult_color(c, comps.object.material.reflective));
}

t_color	refracted_color(t_world w, t_comps comps, int depth)
{
	t_ray	refracted_ray;
	double	n_ratio;
	double	cos_i;
	double	cos_t;
	double	sin2_t;

	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.eyev, comps.normalv);
	sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
	if (comps.object.material.transparency == 0 || depth == 0 || sin2_t > 1)
		return (color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	refracted_ray = ray(comps.under_point, sub_tuple(mult_tuple(comps.normalv, (n_ratio * cos_i) - cos_t),
													mult_tuple(comps.eyev, n_ratio)));
	return (mult_color(color_at(w, refracted_ray, depth - 1), comps.object.material.transparency));
}

/* --------------------------------------------------------- */

int	is_same_object(t_object object1, t_object object2)
{
	return (object1.id == object2.id);
}

int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

int	is_same_hit(t_intersection *hit_list, t_intersection hit)
{
	return (float_compare(hit_list->t, hit.t)
		&& is_same_object(hit_list->object, hit.object));
}

t_intersection	intersection2(double t, t_object s)
{
	return ((t_intersection){.t = t, .object = s, .next = NULL});
}

t_object	get_last_object(t_object *object_list)
{
	t_object	*aux;

	aux = object_list;
	while (aux && aux->next)
		aux = aux->next;
	return (*aux);
}

double	get_n1_refract(t_object *containers)
{
	double	refract;

	if (!containers)
		refract = 1.0;
	else
		refract = get_last_object(containers).material.refractive_index;
	return (refract);
}

void	add_object_to_container(t_object **containers, t_object object)
{
	t_object	*aux;
	t_object	*new_object;

	aux = *containers;
	new_object = malloc(sizeof(t_object));
	*new_object = object;
	new_object->next = NULL;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new_object;
	}
	else
		*containers = new_object;
}

void	remove_object_from_container(t_object **containers, t_object object)
{
	t_object	*aux;
	t_object	*prev;

	aux = *containers;
	prev = NULL;
	while (aux)
	{
		if (is_same_object(*aux, object))
		{
			if (prev)
				prev->next = aux->next;
			else
				*containers = aux->next;
			free(aux);
			break ;
		}
		prev = aux;
		aux = aux->next;
	}
}

int	has_object(t_object *containers, t_object shape)
{
	t_object	*aux;

	aux = containers;
	while (aux)
	{
		if (is_same_object(*aux, shape))
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	update_containers(t_object **containers, t_object object)
{
	if (has_object(*containers, object))
		remove_object_from_container(containers, object);
	else
		add_object_to_container(containers, object);
}

void	object_clear_list(t_object **object_list)
{
	if (object_list && *object_list)
	{
		object_clear_list(&((*object_list)->next));
		free(*object_list);
		*object_list = NULL;
	}
}

void	calculate_index(t_comps *comps, t_intersection *xs)
{
	t_intersection *aux_hit;
	t_object *cnt;

	aux_hit = xs;
	cnt = NULL;
	while (aux_hit)
	{
		if (is_same_hit(aux_hit, intersection2(comps->t, comps->object)))
			comps->n1 = get_n1_refract(cnt);
		update_containers(&cnt, aux_hit->object);
		if (is_same_hit(aux_hit, intersection2(comps->t, comps->object)))
		{
			if (!cnt)
				comps->n2 = 1.0;
			else
				comps->n2 = get_last_object(cnt).material.refractive_index;
			break;
		}
		aux_hit = aux_hit->next;
	}
	object_clear_list(&cnt);
}
