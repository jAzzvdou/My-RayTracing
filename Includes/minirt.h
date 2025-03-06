/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:24:41 by jazevedo          #+#    #+#             */
/*   Updated: 2025/03/06 17:53:25 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//----------| LIBRARIES |----------//
# include <unistd.h>                  //| WRITE, READ
# include <stdlib.h>                  //| MALLOC, FREE, NULL
# include <fcntl.h>                   //| OPEN, CLOSE
# include <stdio.h>                   //| PRINTF
# include <limits.h>                  //| INTMAX, INTMIN
# include <math.h>                    //| SQRT, POW, TAN, COS, SIN
# include <stdbool.h>                 //| TRUE, FALSE
# include "./minilibx-linux/mlx.h"    //| MiniLibX
# include "./MemoryCard/memorycard.h" //| MEMORYCARD

//----------| DEFINES |----------//
//__________ getnextline __________
# define BUFFER_SIZE 4200

//__________ colors __________
# define RED	"\001\033[38;2;255;0;0m\002"
# define GREEN	"\001\033[38;2;0;255;0m\002"
# define BLUE	"\001\033[38;2;0;0;255m\002"
# define YELLOW	"\001\033[38;2;255;255;0m\002"
# define WHITE	"\001\033[38;2;255;255;255m\002"
# define BLACK	"\001\033[38;2;0;0;0m\002"
# define GREY	"\001\033[38;2;128;128;128m\002"
# define BROWN	"\001\033[38;2;150;75;0m\002"
# define ORANGE	"\001\033[38;2;255;165;0m\002"
# define PURPLE	"\001\033[38;2;153;51;153m\002"
# define LILAC	"\001\033[38;2;200;162;200m\002"
# define PINK	"\001\033[38;2;255;203;219m\002"
# define BMPINK	"\001\033[38;2;255;145;175m\002"
# define CYAN	"\001\033[38;2;0;255;255m\002"
# define RESET	"\033[0m"
# define CLEAR	"\033[H\033[J"

//__________ hooks __________
# define ESC       65307
# define DESTROY   17
# define KEY_EVENT 02

//__________ image __________
# define WIDTH  720
# define HEIGHT 720

//__________ errors __________
# define ARGV "Error! Usage: ./miniRT <filename>.\n"
# define FILENAME "Error! File Is Not '.rt'.\n"

//__________ types __________
# define INT 2147483647
# define DOUBLE 179769308

//__________ epsilon __________
# define EPSILON 0.00001

//----------| STRUCTS |----------//
typedef enum e_type
{
	SP,
	PL,
	CY,
	NONE
}	t_type;

typedef enum e_pattern_type
{
	STRIPE,
	GRADIENT,
	RING,
	NO_TYPE
}	t_pattern_type;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_tuple	t_tuple;
typedef struct s_tuple	t_point;
typedef struct s_tuple	t_vector;

struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
};

typedef struct s_light
{
	t_color		intensity;
	t_point		position;
	struct s_light	*next;
}	t_light;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	double	matrix[16];
}	t_matrix;

typedef struct s_pattern
{
	bool	has_pattern;
	t_pattern_type	type;
	t_color	a;
	t_color	b;
	t_matrix	inversed;
	t_matrix	transformed;
}	t_pattern;

typedef struct s_material
{
	t_color	color;
	double	amb;	//| ambient
	double	diff;	//| diffuse
	double	spec;	//| specular
	double	shiny;	//| shininess
	double	reflective; //| vai de 0 até 1, sendo 0 totalmente opaco e 1 totalmente espelhado
	double	transparency;
	double	refractive_index;
	t_pattern	pattern;
}	t_material;

typedef struct s_object
{
	t_type		type;
	int			id;
	//| Objects
	t_point			origin;		//| Para esfera, plano e cilindro.
	t_vector		normal;		//| Para plano e cilindro.
	double			radius;		//| Para esfera e cilindro.
	double			height;		//| Para cilindro.
	//| Ver se o objeto foi modificado ou permanece original.
	t_matrix		transformed;	//| Para transladar, rotacionar e escalar. Se for igual, então transformed = identity.
	t_matrix		inversed;	//| Para inverter a matriz. Se for igual, então inversed = identity.
	t_matrix		transposed;	//| Para transpor a matriz. Se for igual, então transposed = identity.
	t_material		material;
	struct s_object	*next;
}	t_object;

typedef struct s_world
{
	t_light		*light;
	t_object	*object;
}	t_world;

typedef struct s_minilibx
{
	int		bpp;
	int		linelen;
	int		endian;
	char	*addr;
	void	*mlx;
	void	*win;
	void	*img;
}	t_minilibx;

typedef struct s_canvas
{
	int		width;
	int		height;
	t_color	*pixel; //| Pixel da tela, todos começam em 0.
}	t_canvas;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_intersection
{
	double					t;
	t_object				object;
	struct s_intersection	*next;
}	t_intersection;

typedef struct s_comps
{
	double		t;
	double		n1;
	double		n2;
	t_object	object;
	t_point		point;
	t_point		over_point;
	t_point		under_point;
	t_vector	eyev;
	t_vector	normalv;
	t_vector	reflectv;
	bool		in_shadow;
	bool		inside;
}	t_comps;

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
}	t_camera;

//----------| FUNCTIONS |----------//
void		screen(void);
t_canvas	render(t_world w, t_camera cam);
void		render_tests(t_minilibx *libx);

//__________ color __________
t_color	color(double r, double g, double b);
t_color	add_color(t_color a, t_color b);
t_color	sub_color(t_color a, t_color b);
t_color	mult_color(t_color a, double b);
t_color	hadama_color(t_color a, t_color b);
t_color	convert_color(t_color a);
int		color_to_int(t_color a);

//__________ tuple __________
t_tuple	tuple(double x, double y, double z, double w);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	sub_tuple(t_tuple a, t_tuple b);
t_tuple	mult_tuple(t_tuple a, double b);
t_tuple	inverse_tuple(t_tuple a);
int		comp_tuple(t_tuple a, t_tuple b);

//__________ point __________
t_point	point(double x, double y, double z);

//__________ vector __________
t_vector	vector(double x, double y, double z);
t_vector	normalize(t_vector a);
t_vector	cross(t_vector a, t_vector b);
double	magnitude(t_vector a);
double	dot(t_vector a, t_vector b);

//__________ canvas __________
t_canvas	create_canvas(int width, int height);
void	draw_pixel(t_minilibx *libx, int x, int y, int color);
void	set_canvas_pixel(t_canvas *canvas, int x, int y, t_color color);
t_color	pixel_at(t_canvas *canvas, int x, int y);
void	draw_canvas(t_minilibx *libx, t_canvas *canvas);
void	canvas_to_ppm(t_canvas canvas, char *filename);

//__________ matrix __________
void	set_index(t_matrix *a, int x, int y, double value);
double	get_index(t_matrix *a, int x, int y);
t_matrix	mult_matrix(t_matrix a, t_matrix b);
t_tuple	mult_matrix_tuple(t_matrix a, t_tuple b);
t_matrix	identity(void);
t_matrix	transpose(t_matrix a);
t_matrix	submatrix(t_matrix a, int x, int y);
double	minor(t_matrix a, int x, int y);
double	cofactor(t_matrix a, int x, int y);
t_matrix	inverse(t_matrix a);
double	determinant(t_matrix a);

//__________ transformations __________
t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	shearing(double *x, double *y, double *z);

//__________ rotations __________
t_matrix	rotationx(double rad);
t_matrix	rotationy(double rad);
t_matrix	rotationz(double rad);

//__________ rays __________
t_ray	ray(t_point p, t_vector v);
t_point	position(t_ray r, double t);
double	bhaskara(t_object o, t_ray r);
void intersect(t_intersection **list, t_object o, t_ray r);
void	add_intersection(t_intersection **list, t_intersection inter);
t_intersection	intersection(t_object o, double t);
int	count_intersection(t_intersection *list);
t_intersection	*hit(t_intersection *inter);
void	set_transform(t_object *o, t_matrix m);

//__________ objects __________
t_object	new_object(t_type type);

//__________ light __________
t_vector	normal_at(t_object o, t_point p);
t_vector	reflect(t_vector in, t_vector normal);
t_light	point_light(t_point p, t_color c);
t_color	lighting(t_light l, t_comps comps);
t_material	material(void);

//__________ world __________
t_world	world(void);
t_world	default_world(void);
void	add_light(t_light **l1, t_light l2);
void	add_object(t_object **obj1, t_object obj2);
t_intersection	*intersect_world(t_world w, t_ray r);
t_comps	prepare_computations(t_intersection inter, t_ray ray, t_intersection *xs);
void	calculate_index(t_comps *comps, t_intersection *xs);
t_color	shade_hit(t_world w, t_comps comps, int remaining);
t_color	color_at(t_world w, t_ray r, int remaining);
t_matrix	view_transform(t_point from, t_point to, t_vector up);
t_camera	camera(int hsize, int vsize, double fov);
t_ray	ray_for_pixel(t_camera c, int x, int y);

//__________ pattern __________
t_pattern	new_pattern(t_pattern_type type, t_color a, t_color b);
t_color	pattern_at_object(t_pattern pattern, t_object obj, t_point point);
void	set_pattern_transform(t_pattern *p, t_matrix transform);
t_color	stripe_at(t_pattern p, t_point pt);
t_color	gradient_at(t_pattern p, t_point pt);
t_color	ring_at(t_pattern p, t_point pt);

//__________ reflection __________
t_color	reflected_color(t_world w, t_comps comps, int remaining);
t_color	refracted_color(t_world w, t_comps comps, int depth);

//----------| ERRORS |----------//
void	err(char *color1, char *error, char *color2);

//----------| CLEANERS |----------//

//----------| UTILS |----------//

//__________ space.c __________
int		is_space(int c);
void	skip_spaces(char **s);

//__________ splitline.c __________
char	**splitline(char const *s, char c);

//__________ get_next_line.c __________
char	*get_next_line(int fd);

//__________ lib1.c __________
size_t	my_strlen(const char *s);
int		my_strcmp(const char *s1, const char *s2);
int		my_strncmp(const char *s1, const char *s2, size_t n);
int		revstrncmp(char *s1, char *s2, int n);
char	*my_strchr(const char *s, int c);

//__________ lib2.c __________
char	*my_strjoin(char *s1, char *s2);
char	*my_substr(char const *s, unsigned int start, size_t len);
void	my_bzero(void *s, size_t n);

//__________ lib3.c __________
size_t	matrixlen(char **matrix);
int		my_atoi(const char *nptr);
double	my_atod(const char *nptr);

//__________ lib4.c __________
int		my_isdigit(int c);
int		is_int(char *s);
int		is_double(char *s);
int		onlynumber(char *s, int type);

//__________ lib5.c __________
char	*my_strdup(const char *s);
char	*my_itoa(int n);

#endif //| MINIRT_H
