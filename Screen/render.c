#include "../Includes/minirt.h"

t_object	glass_sphere(void)
{
	t_object sp = new_object(SP);
	sp.material.transparency = 0;
	sp.material.refractive_index = 1.5;
	return (sp);
}

void render_scene(t_minilibx *libx)
{
	t_object floor = new_object(PL);
	floor.material = material();
	floor.material.color = color(1, 0.9, 0.9);
	floor.material.spec = 0;
	floor.material.refractive_index = 10;
	floor.material.reflective = 1;
	set_transform(&floor, translation(0, -1, 0));

	t_object sphere = new_object(SP);
	sphere.material.pattern = new_pattern(TEXTURE, color(1, 1, 1), color(0, 0, 0), libx->mlx);
	set_pattern_transform(&sphere.material.pattern, scaling(1, 1, 1));
	set_transform(&sphere, translation(0, 0, 2));

	t_world w = world();
	t_camera cam = camera(HEIGHT, WIDTH, M_PI / 3);
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	add_object(&w.object, sphere);
	//add_object(&w.object, floor);

	t_light light = point_light(point(-10, 10, -10), color(1, 1, 1));
	add_light(&w.light, light);

	t_canvas canvas = render(w, cam);
	draw_canvas(libx, &canvas);
}

void print_point(t_tuple t)
{
	printf("x: %f y: %f z: %f w: %f\n", t.x, t.y, t.z, t.w);
}

void print_color(t_color c)
{
	printf("r: %f g: %f b: %f\n", c.r, c.g, c.b);
}

void print_matrix(t_matrix m)
{
	printf("%f %f %f %f\n", get_index(&m, 0, 0), get_index(&m, 1, 0), get_index(&m, 2, 0), get_index(&m, 3, 0));
	printf("%f %f %f %f\n", get_index(&m, 0, 1), get_index(&m, 1, 1), get_index(&m, 2, 1), get_index(&m, 3, 1));
	printf("%f %f %f %f\n", get_index(&m, 0, 2), get_index(&m, 1, 2), get_index(&m, 2, 2), get_index(&m, 3, 2));
	printf("%f %f %f %f\n", get_index(&m, 0, 3), get_index(&m, 1, 3), get_index(&m, 2, 3), get_index(&m, 3, 3));
}

t_canvas render(t_world w, t_camera cam)
{
	int xy[2];
	t_ray r;
	t_color c;
	t_canvas image;

	image = create_canvas(cam.hsize, cam.vsize);
	xy[1] = 0;
	while (xy[1] < cam.vsize)
	{
		xy[0] = 0;
		while (xy[0] < cam.hsize)
		{
			r = ray_for_pixel(cam, xy[0], xy[1]);
			c = color_at(w, r, 4);
			set_canvas_pixel(&image, xy[0], xy[1], c);
			xy[0]++;
		}
		xy[1]++;
	}
	return (image);
}

t_intersection *inter_index(t_intersection *inter, int index)
{
	int i;
	t_intersection *aux;

	i = 0;
	aux = inter;
	while (aux && i < index)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}

void render_tests(t_minilibx *libx)
{
	render_scene(libx);
	(void)libx;
/*	t_object cn = new_object(CN);
    // Test case 1: point(0, 0, 0)
    t_vector n1 = normal_at(cn, point(0, 0, 0));
    printf("n1 = (%f, %f, %f)\n", n1.x, n1.y, n1.z);

    // Test case 2: point(1, 1, 1)
    t_vector n2 = normal_at(cn, point(1, 1, 1));
    printf("n2 = (%f, %f, %f)\n", n2.x, n2.y, n2.z);

    // Test case 3: point(-1, -1, 0)
    t_vector n3 = normal_at(cn, point(-1, -1, 0));
    printf("n3 = (%f, %f, %f)\n", n3.x, n3.y, n3.z);*/
}
