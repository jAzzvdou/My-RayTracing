#include "../Includes/minirt.h"

void	render_sphere(t_canvas *canvas)
{
	int xy[2];
	t_ray r;
	t_object sphere;
	t_light light;
	t_point point_inter;
	t_vector normalv, eyev;
	t_intersection *h, *list;
	t_color pixel_color;

	sphere = new_object(SP);
	sphere.material.color = color(1, 0.2, 1);
	light = point_light(point(-10, 10, -10), color(1, 1, 1));
	xy[1] = 0;
	while (xy[1] < canvas->height)
	{
		xy[0] = 0;
		while (xy[0] < canvas->width)
		{
			list = NULL;
			r = ray(point(0, 0, -5),
					normalize(vector((xy[0] - canvas->width / 2.0) / (double)canvas->width,
							(canvas->height / 2.0 - xy[1]) / (double)canvas->height,
							1.0)));
			intersect(&list, sphere, r);
			h = hit(list);
			if (h)
			{
				point_inter = position(r, h->t);
				normalv = normal_at(h->object, point_inter);
				eyev = inverse_tuple(r.direction);
				pixel_color = lighting(h->object.material, light, point_inter, eyev, normalv);
				set_canvas_pixel(canvas, xy[0], xy[1], pixel_color);
			}
			xy[0]++;
		}
		xy[1]++;
	}
}

t_canvas	render(t_world w, t_camera cam)
{
	int		xy[2];
	t_ray		r;
	t_color		c;
	t_canvas	image;

	image = create_canvas(cam.hsize, cam.vsize);
	xy[1] = 0;
	while (xy[1] < cam.vsize)
	{
		xy[0] = 0;
		while (xy[0] < cam.hsize)
		{
			r = ray_for_pixel(cam, xy[0], xy[1]);
			c = color_at(w, r);
			set_canvas_pixel(&image, xy[0], xy[1], c);
			xy[0]++;
		}
		xy[1]++;
	}
	return (image);
}

void	render_scene1(t_minilibx *libx)
{
	t_object floor;
	floor = new_object(SP);
	floor.transformed = scaling(10, 0.01, 10);
	floor.material = material();
	floor.material.color = color(1, 0.9, 0.9);
	floor.material.spec = 0;

	t_object left_wall;
	left_wall = new_object(SP);
	left_wall.transformed = mult_matrix(translation(0, 0, 5), rotationy(-M_PI / 4));
	left_wall.transformed = mult_matrix(left_wall.transformed, rotationx(M_PI / 2));
	left_wall.transformed = mult_matrix(left_wall.transformed, scaling(10, 0.01, 10));
	left_wall.material = floor.material;

	t_object right_wall;
	right_wall = new_object(SP);
	right_wall.transformed = mult_matrix(translation(0, 0, 5), rotationy(M_PI / 4));
	right_wall.transformed = mult_matrix(right_wall.transformed, rotationx(M_PI / 2));
	right_wall.transformed = mult_matrix(right_wall.transformed, scaling(10, 0.01, 10));

	t_object middle;
	middle = new_object(SP);
	middle.transformed = translation(-0.5, 1, 0.5);
	middle.material = material();
	middle.material.color = color(0.1, 1, 0.5);
	middle.material.diff = 0.7;
	middle.material.spec = 0.3;

	t_object right;
	right = new_object(SP);
	right.transformed = mult_matrix(translation(-0.5, 1, 0.5), scaling(0.5, 0.5, 0.5));
	right.material = material();
	right.material.color = color(0.5, 1, 0.1);
	right.material.diff = 0.7;
	right.material.spec = 0.3;

	t_object left;
	left = new_object(SP);
	left.transformed = mult_matrix(translation(0.5, 1, 0.5), scaling(0.5, 0.5, 0.5));
	left.material = material();
	left.material.color = color(1, 0.8, 0.1);
	left.material.diff = 0.7;
	left.material.spec = 0.3;

	t_light light;
	light = point_light(point(-10, 10, -10), color(1, 1, 1));

	t_world w;
	w = world();
	add_light(&w.light, light);
	add_object(&w.object, floor);
	add_object(&w.object, left_wall);
	add_object(&w.object, right_wall);
	add_object(&w.object, middle);
	add_object(&w.object, right);
	add_object(&w.object, left);

	t_camera cam;
	cam = camera(100, 50, M_PI / 3);
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	t_canvas canvas;
	canvas = render(w, cam);
	//canvas = render(default_world(), cam);

	draw_canvas(libx, &canvas);
}

void	render_tests(t_minilibx *libx)
{
	//| TESTE ESFERA ROSA
/*	t_canvas	canvas;
	canvas = create_canvas(WIDTH, HEIGHT);
	render_sphere(&canvas);
	draw_canvas(libx, &canvas);
*/
	//| TESTE PRIMEIRA CENA
	//render_scene1(libx);

	//| TESTE INTERSECT_WORLD()
/*	(void)libx;
	t_world w = default_world();
	t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersection *xs = intersect_world(w, r);
	int count = count_intersection(xs);
	printf("count: %i.\n", count);
	while (xs)
	{
		printf("xs->t: %f.\n", xs->t);
		xs = xs->next;
	}
	int i = 0;
	t_object *tmp = w.object;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	printf("Objetos: %i.\n", i);
*/
	//| TESTE PREPARE_COMPUTATIONS()
/*	(void)libx;
	t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_object sphere = new_object(SP);
	t_intersection i = intersection(sphere, 1);
	t_comps comps = prepare_computations(i, r);
	printf("x: %f y: %f z: %f.\n", comps.point.x, comps.point.y, comps.point.z);
	printf("x: %f y: %f z: %f.\n", comps.eyev.x, comps.eyev.y, comps.eyev.z);
	printf("x: %f y: %f z: %f.\n", comps.normalv.x, comps.normalv.y, comps.normalv.z);
	int in = 0;
	if (comps.inside == true)
		in = 1;
	printf("inside: %i.\n", in);
*/
	//| TESTE DE SHADE_HIT()
/*	(void)libx;
	t_world w = default_world();
	t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_object *sphere = w.object->next;
	t_intersection i = intersection(*sphere, 0.5);
	t_comps comps = prepare_computations(i, r);
	t_color c = shade_hit(w, comps);
	printf("r: %f g: %f b: %f.\n", c.r, c.g, c.b);
*/
	//| TESTE DE COLOR_AT()
/*	(void)libx;
	t_world w = default_world();
	t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_color c = color_at(w, r);
	printf("r: %f g: %f b: %f.\n", c.r, c.g, c.b);

	t_object *o1 = w.object;
	o1->material.amb = 1;
	t_object *o2 = w.object->next;
	o2->material.amb = 1;
	r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	c = color_at(w, r);
	printf("\nr: %f g: %f b: %f.\n", o2->material.color.r, o2->material.color.g, o2->material.color.b); 
	printf("r: %f g: %f b: %f.\n", c.r, c.g, c.b);
*/
	//| TESTE DE RAY_FOR_PIXEL()
/*	(void)libx;
	t_camera cam = camera(201, 101, M_PI / 2);
	t_ray r = ray_for_pixel(cam, 0, 0);
	printf("x: %f y: %f z: %f.\n", r.origin.x, r.origin.y, r.origin.z);
	printf("x: %f y: %f z: %f.\n", r.direction.x, r.direction.y, r.direction.z);
*/
	(void)libx;
	t_world w = default_world();
	t_camera cam = camera(11, 11, M_PI / 2);
	cam.transform = view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));
	t_canvas canvas = render(w, cam);
	t_color c = pixel_at(&canvas, 5, 5);
	printf("r: %f g: %f b: %f.\n", c.r, c.g, c.b);
	/* ACHO QUE VIEW_TRANSFORM() ESTÁ ERRADA */
}	
