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

	// Criar o chão
	t_object floor = new_object(PL);
	floor.material = material();
	floor.material.color = color(1, 0.9, 0.9);
	floor.material.spec = 0;
	floor.material.refractive_index = 10;
	floor.material.reflective = 1;
	set_transform(&floor, translation(0, -1, 0));

	// Criar esfera opaca atrás da esfera de vidro
	t_object opaque_sphere = new_object(SP);
	opaque_sphere.material.color = color(0, 1, 0); // Vermelha
	set_transform(&opaque_sphere, translation(0, 0, 3));

	// Criar mundo e câmera
	t_world w = world();
	t_camera cam = camera(HEIGHT, WIDTH, M_PI / 3);
	cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	add_object(&w.object, opaque_sphere);
	add_object(&w.object, floor);

	// Criar luz
	t_light light = point_light(point(-10, 10, -10), color(1, 1, 1));
	add_light(&w.light, light);

	// Renderizar e desenhar
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
	/*(void)libx;
	t_world w = default_world();

	t_object plane = new_object(PL);
	plane.material.transparency = 0.5;
	plane.material.refractive_index = 1.5;
	set_transform(&plane, translation(0, -1, 0));
	add_object(&w.object, plane);

	t_object ball = new_object(SP);
	ball.material.color = color(1, 0, 0);
	ball.material.amb = 0.5;
	set_transform(&ball, translation(0, -3.5, -0.5));
	add_object(&w.object, ball);

	t_ray r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	t_intersection *xs = NULL;
	add_intersection(&xs, intersection(plane, sqrt(2)));

	t_comps comps = prepare_computations(xs[0], r, xs);
	t_color result = shade_hit(w, comps, 5);

	printf("Expected: R -> 0.93642 | G -> 0.68642 | B -> 0.68642 \n");
	printf("Result: R -> %f| G -> %f| B -> %f\n", result.r, result.g, result.b);*/

}
