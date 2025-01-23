#include "Includes/minirt.h"

static void	free_canvas_pixel(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->height)
	{
		canvas->pixel[i] = memcard(canvas->pixel[i], DEFAULT, FREE, 0);
		i++;
	}
	canvas->pixel = memcard(canvas->pixel, DEFAULT, FREE, 0);
}

t_canvas	create_canvas(int width, int height)
{
	int	i;
	int	j;
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.pixel = (t_color **)memcard(NULL, DEFAULT, MALLOC, sizeof(t_color *) * height);
	if (!canvas.pixel)
		return (canvas.pixel = memcard(canvas.pixel, DEFAULT, FREE, 0), (t_canvas){0});
	i = 0;
	while (i < height)
	{
		canvas.pixel[i] = (t_color *)memcard(NULL, DEFAULT, MALLOC, sizeof(t_color) * width);
		if (!canvas.pixel[i])
		{
			free_canvas_pixel(&canvas);
			return (canvas.pixel = memcard(canvas.pixel, DEFAULT, FREE, 0), (t_canvas){0});
		}
		j = 0;
		while (j < width)
			canvas.pixel[i][j++] = (t_color){0, 0, 0};
		i++;
	}
	return (canvas);
}

void	draw_pixel(t_minilibx *libx, int x, int y, int color)
{
	char	*pixel;

	if (y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
		return ;
	pixel = libx->addr + (y * libx->linelen + x * (libx->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	set_canvas_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	if (y >= canvas->height || x >= canvas->width || x < 0 || y < 0)
		return ;
	canvas->pixel[y][x] = color;
}

void	pixel_at_canvas(t_canvas *canvas, int x, int y, t_color *color)
{
	if (y >= canvas->height || x >= canvas->width || x < 0 || y < 0)
		return ;
	*color = canvas->pixel[y][x];
}

void	clear_canvas(t_canvas *canvas)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
			canvas->pixel[i][j++] = (t_color){0, 0, 0};
		i++;
	}
}

void	draw_canvas(t_minilibx *libx, t_canvas *canvas)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			draw_pixel(libx, j, i, color_to_int(canvas->pixel[i][j]));
			j++;
		}
		i++;
	}
}

void	write_fd(int fd, char *s)
{
	write(fd, s, my_strlen(s));
}

void	canvas_to_ppm(t_canvas canvas, char *filename)
{
	int		fd;
	int		x;
	int		y;
	t_color	color;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	write_fd(fd, "P3\n");
	write_fd(fd, my_itoa(canvas.width));
	write_fd(fd, " ");
	write_fd(fd, my_itoa(canvas.height));
	write_fd(fd, "\n255\n");
	y = 0;
	while (y < canvas.height)
	{
		x = 0;
		while (x < canvas.width)
		{
			pixel_at_canvas(&canvas, x, y, &color);
			write_fd(fd, my_itoa(color.r));
			write_fd(fd, " ");
			write_fd(fd, my_itoa(color.g));
			write_fd(fd, " ");
			write_fd(fd, my_itoa(color.b));
			write_fd(fd, "\n");
			x++;
		}
		y++;
	}
	close(fd);
}
