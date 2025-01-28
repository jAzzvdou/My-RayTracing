#include "../Includes/minirt.h"

void	render_sphere(t_canvas *canvas)
{
	int	xy[2];
	t_ray	r;
	t_intersections	inter;
	t_object	sphere;

	sphere = new_object(SP);
	xy[1] = 0;
	while (xy[1] < canvas->height)
	{
		xy[0] = 0;
		while (xy[0] < canvas->width)
		{
			r = ray(point(0, 0, -5), normalize(vector((xy[0] - canvas->width / 2.0) / (double)canvas->width,
								(canvas->height / 2.0 - xy[1]) / (double)canvas->height,
								1.0)));
			inter = intersect(sphere, r);
			t_intersection h = hit(inter);
			if (h.t > 0)
				set_canvas_pixel(canvas, xy[0], xy[1], color(1, 1, 1));
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
