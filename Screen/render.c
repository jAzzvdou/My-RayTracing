#include "../Includes/minirt.h"

void	render_scene(t_minilibx *libx)
{
	t_object floor = new_object(PL);
	floor.material.pattern = new_pattern(RING, color(1, 1, 0), color(0, 1, 1));
	set_pattern_transform(&floor.material.pattern, mult_matrix(scaling(2, 2, 2), rotationy(30 * M_PI / 180)));
	floor.material.color = color(0.3, 0.3, 0.3);

	t_object middle;
	middle = new_object(SP);
	set_transform(&middle, translation(-0.5, 1, 0.5));
	middle.material = material();
	middle.material.color = color(1, 0, 0);
	middle.material.diff = 0.7;
	middle.material.spec = 0.3;
	middle.material.pattern = new_pattern(RING, color (1, 1, 0), color(1, 0, 1));
	set_pattern_transform(&middle.material.pattern, scaling(0.2, 0.2, 0.2));


	t_object right;
	right = new_object(SP);
	set_transform(&right, mult_matrix(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)));
	right.material = material();
	right.material.color = color(0, 1, 0);
	right.material.diff = 0.7;
	right.material.spec = 0.3;
	right.material.pattern = new_pattern(STRIPE, color (1, 1, 0), color(0, 1, 1));
	set_pattern_transform(&right.material.pattern, scaling(0.5, 0.5, 0.5));

	t_object left;
	left = new_object(SP);
	set_transform(&left, mult_matrix(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)));
	left.material = material();
	left.material.color = color(0, 0, 1);
	left.material.diff = 0.7;
	left.material.spec = 0.3;
	left.material.pattern = new_pattern(GRADIENT, color (1, 0, 1), color(1, 1, 1));
	set_pattern_transform(&left.material.pattern, scaling(2, 2, 2));

	t_light light1;
	light1 = point_light(point(-10, 10, -10), color(1, 1, 1));

	t_world w;
	w = world();
	add_light(&w.light, light1);	
	add_object(&w.object, floor);
	add_object(&w.object, middle);
	add_object(&w.object, right);
	add_object(&w.object, left);

	t_camera cam;
	cam = camera(WIDTH, HEIGHT, M_PI / 3);
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	t_canvas canvas;
	canvas = render(w, cam);

	draw_canvas(libx, &canvas);
}

void	print_point(t_tuple t)
{
	printf("x: %f y: %f z: %f w: %f\n", t.x, t.y, t.z, t.w);
}

void	print_color(t_color c)
{
	printf("r: %f g: %f b: %f\n", c.r, c.g, c.b);
}

void	print_matrix(t_matrix m)
{
	printf("%f %f %f %f\n", get_index(&m, 0, 0), get_index(&m, 1, 0), get_index(&m, 2, 0), get_index(&m, 3, 0));
	printf("%f %f %f %f\n", get_index(&m, 0, 1), get_index(&m, 1, 1), get_index(&m, 2, 1), get_index(&m, 3, 1));
	printf("%f %f %f %f\n", get_index(&m, 0, 2), get_index(&m, 1, 2), get_index(&m, 2, 2), get_index(&m, 3, 2));
	printf("%f %f %f %f\n", get_index(&m, 0, 3), get_index(&m, 1, 3), get_index(&m, 2, 3), get_index(&m, 3, 3));
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

void	render_tests(t_minilibx *libx)
{
	render_scene(libx);
}	
