#include "../Includes/minirt.h"
/*
void	render_sphere(t_canvas *canvas)
{
	int	xy[2];
	t_ray	r;
	t_object	sphere;

	sphere = new_object(SP);
	xy[1] = 0;
	while (xy[1] < canvas->height)
	{
		xy[0] = 0;
		while (xy[0] < canvas->width)
		{
			r = ray(point(0, 0, -5),
				normalize(vector((xy[0] - canvas->width / 2.0) / (double)canvas->width,
						(canvas->height / 2.0 - xy[1]) / (double)canvas->height,
						1.0)));
			t_intersection h = hit(intersect(sphere, r));
			if (h.t > 0)
				set_canvas_pixel(canvas, xy[0], xy[1], color(1, 0, 0));
			xy[0]++;
		}
		xy[1]++;
	}
}
*/

void	render_sphere(t_canvas *canvas)
{
	int xy[2];
	t_ray r;
	t_object sphere;
	t_light light;
	t_point point_inter;
	t_vector normalv, eyev;
	t_intersection h;
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
			r = ray(point(0, 0, -5),
					normalize(vector((xy[0] - canvas->width / 2.0) / (double)canvas->width,
							(canvas->height / 2.0 - xy[1]) / (double)canvas->height,
							1.0)));
			h = hit(intersect(sphere, r));
			if (h.t > 0)
			{
				point_inter = position(r, h.t);
				normalv = normal_at(h.object, point_inter);
				eyev = inverse_tuple(r.direction);
				pixel_color = lighting(h.object.material, light, point_inter, eyev, normalv);
				set_canvas_pixel(canvas, xy[0], xy[1], pixel_color);
			}
			xy[0]++;
		}
		xy[1]++;
	}
}

void	render(t_minilibx *libx)
{
	t_canvas	canvas;

	canvas = create_canvas(WIDTH, HEIGHT);
	render_sphere(&canvas);
	draw_canvas(libx, &canvas);
}
