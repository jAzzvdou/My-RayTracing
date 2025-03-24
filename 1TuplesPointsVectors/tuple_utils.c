#include "../Includes/minirt.h"

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	return (tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	return (tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}

t_tuple	mult_tuple(t_tuple a, double b)
{
	return (tuple(a.x * b, a.y * b, a.z * b, a.w * b));
}

t_tuple	inverse_tuple(t_tuple a)
{
	return (tuple(-a.x, -a.y, -a.z, -a.w));
}

int	comp_tuple(t_tuple a, t_tuple b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w)
		return (1);
	return (0);
}
