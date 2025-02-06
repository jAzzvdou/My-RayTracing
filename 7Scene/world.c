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

t_color	color_at(t_world w, t_ray r)
{
	t_intersection *h;
	t_comps	comps;

	h = hit(intersect_world(w, r));
	if (!h)
		return (color(0, 0, 0));
	comps = prepare_computations(h, r);
	return (shade_hit(w, comps));
}

t_matrix	get_orientation(t_vector v[4])
{
	t_matrix	orientation;

	orientation = identity();
	set_index(&orientation, 0, 0, v[2].x);
	set_index(&orientation, 0, 1, v[2].y);
	set_index(&orientation, 0, 2, v[2].z);
	set_index(&orientation, 1, 0, v[3].x);
	set_index(&orientation, 1, 1, v[3].y);
	set_index(&orientation, 1, 2, v[3].z);
	set_index(&orientation, 2, 0, -v[0].x);
	set_index(&orientation, 2, 1, -v[0].y);
	set_index(&orientation, 2, 2, -v[0].z);
	return (orientation);
}

t_matrix	view_transform(t_point from, t_point to, t_vector up)
{
	t_vector	v[4]; //| 0: forward, 1: upn, 2: left, 3: true_up
	t_matrix	orientation;
	t_matrix	transl;

	v[0] = normalize(sub_tuple(to, from)); //| forward
	v[1] = normalize(up);                  //| upn
	v[2] = cross(v[0], v[1]);              //| left
	v[3] = cross(v[2], v[0]);              //| true_up
	orientation = get_orientation(v);
	transl = translation(-from.x, -from.y, -from.z);
	return (mult_matrix(orientation, transl));
}

t_camera	camera(int hsize, int vsize, double fov)
{
	double	half_view;
	double	aspect;
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
	c.transform = identity();
	half_view = tan(fov / 2);
	aspect = (double)hsize / (double)vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}

t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	double	d[4]; //| xoffset, yoffset, world_x, world_y
	t_point	pixel;
	t_point	origin;
	t_vector	direction;

	d[0] = (px + 0.5) * c.pixel_size;
	d[1] = (py + 0.5) * c.pixel_size;
	d[2] = c.half_width - d[0];
	d[3] = c.half_height - d[1];
	pixel = mult_matrix_tuple(inverse(c.transform), point(d[2], d[3], -1));
	origin = mult_matrix_tuple(inverse(c.transform), point(0, 0, 0));
	direction = normalize(sub_tuple(pixel, origin));
	return (ray(origin, direction));
}
