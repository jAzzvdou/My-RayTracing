#include "../Includes/minirt.h"

t_color color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color add_color(t_color a, t_color b)
{
	return (color(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color sub_color(t_color a, t_color b)
{
	return (color(a.r - b.r, a.g - b.g, a.b - b.b));
}

t_color mult_color(t_color a, double b)
{
	return (color(a.r * b, a.g * b, a.b * b));
}

t_color hadama_color(t_color a, t_color b)
{
	return (color((a.r * b.r), (a.g * b.g), (a.b * b.b)));
}

t_color convert_color(t_color a)
{
	return (color(a.r / 255, a.g / 255, a.b / 255));
}

int	color_to_int(t_color a)
{
	int	r;
	int	g;
	int	b;

	r = (int)(a.r * 255.999);
	g = (int)(a.g * 255.999);
	b = (int)(a.b * 255.999);
	return (r << 16 | g << 8 | b);
}
