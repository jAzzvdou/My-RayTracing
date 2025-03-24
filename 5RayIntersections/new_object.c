#include "../Includes/minirt.h"

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
