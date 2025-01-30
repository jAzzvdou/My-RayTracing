#include "../Includes/minirt.h"

t_object	fill_sphere(t_object obj)
{
	obj.type = SP;
	obj.origin = point(0, 0, 0);
	obj.radius = 1;
	return (obj);
}

t_material	material(void)
{
	t_material	m;

	m.color = color(1, 1, 1);
	m.amb = 0.1;
	m.diff = 0.9;
	m.spec = 0.9;
	m.shiny = 200.0;
	return (m);
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
