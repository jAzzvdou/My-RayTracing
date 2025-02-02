#include "../Includes/minirt.h"

t_vector	sphere_normal_at(t_point p)
{
	t_vector	normal;

	normal = sub_tuple(p, point(0, 0, 0));
	normal.w = 0;
	return (normalize(normal));
}

t_vector	object_normal_at(t_object o, t_point p)
{
	if (o.type == SP)
		return (sphere_normal_at(p));
	//Adicionar if else para todos os objetos
	return ((t_vector){0, 0, 0, 0});
}

t_vector	normal_at(t_object o, t_point p)
{
	t_point		obj_point;
	t_point		obj_normal;
	t_vector	world_normal;

	obj_point = mult_matrix_tuple(o.inversed, p);
	obj_normal = object_normal_at(o, obj_point);
	world_normal = mult_matrix_tuple(o.transposed, obj_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}


