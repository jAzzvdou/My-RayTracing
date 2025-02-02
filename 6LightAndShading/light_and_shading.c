#include "../Includes/minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	return (sub_tuple(in, mult_tuple(normal, 2 * dot(in, normal))));
}

t_light	point_light(t_point p, t_color c)
{
	t_light	light;

	light.position = p;
	light.intensity = c;
	light.next = NULL;
	return (light);
}

t_color	clamp_color(t_color c)
{
	c.r = fmin(fmax(c.r, 0), 1);
	c.g = fmin(fmax(c.g, 0), 1);
	c.b = fmin(fmax(c.b, 0), 1);
	return (c);
}

t_color	lighting(t_material m, t_light l, t_point p, t_vector eyev, t_vector normalv)
{
	double	d[3];		//| 0: light_dot_normal, 1: reflect_dot_eye, 2: factor
	t_color	c[4];		//| 0: effective_color, 1: ambient, 2: diffuse, 3: specular
	t_vector	v[2];	//| 0: lightv, 1: reflectv

	c[0] = hadama_color(m.color, l.intensity);
	v[0] = normalize(sub_tuple(l.position, p));
	c[1] = mult_color(c[0], m.amb);
	d[0] = dot(v[0], normalv);
	if (d[0] < 0)
		return (c[1]);
	c[2] = mult_color(c[0], m.diff * d[0]);
	v[1] = reflect(inverse_tuple(v[0]), normalv);
	d[1] = dot(v[1], eyev);
	if (d[1] <= 0)
		c[3] = color(0, 0, 0);
	else
	{
		d[2] = pow(d[1], m.shiny);
		c[3] = mult_color(l.intensity, m.spec * d[2]);
	}
	return (clamp_color(add_color(add_color(c[1], c[2]), c[3])));
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
