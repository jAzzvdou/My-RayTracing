/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:24:41 by jazevedo          #+#    #+#             */
/*   Updated: 2025/01/23 23:40:05 by jazevedo         ###   ########.fr       */
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
# define WIDTH  1281
# define HEIGHT 721

//__________ errors __________
# define ARGV "Error! Usage: ./miniRT <filename>.\n"
# define FILENAME "Error! File Is Not '.rt'.\n"

//__________ types __________
# define INT 2147483647
# define DOUBLE 179769308

//----------| STRUCTS |----------//
typedef enum e_type
{
	A,
	C,
	L,
	SP,
	PL,
	CY
}	t_type;

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
	t_color	intensity;
	t_point	position;
	struct s_light	*next;
}	t_light;

typedef struct s_object
{
	t_type	type;
	t_point	origin;
	t_vector	normal;
	double	radius;
	double	height;
	t_color	color;
	struct s_object	*next;
}	t_object;

typedef struct s_map
{
	t_light		*light;
	t_object	*object;
	t_scene		scene; //| Fazer
}	t_map;

typedef struct s_minilibx
{
	int		bpp;
	int		linelen;
	int		endian;
	char	*addr;
	void	*mlx;
	void	*win;
	void	*img;
	t_map		*map; // TEMPORÁRIO
}	t_minilibx;

typedef struct s_canvas
{
	int		width;
	int		height;
	t_color	*pixel; //| Pixel da tela, todos começam em 0.
}	t_canvas;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	double	matrix[16];
}	t_matrix;

//----------| FUNCTIONS |----------//

//__________ color __________
t_color	color(double r, double g, double b);
t_color	add_color(t_color a, t_color b);
t_color	sub_color(t_color a, t_color b);
t_color	mult_color(t_color a, double b);
t_color	average_color(t_color a, t_color b);
t_color convert_color(t_color a);
int	color_to_int(t_color a);

//__________ tuple __________
t_tuple	tuple(double x, double y, double z, double w);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	sub_tuple(t_tuple a, t_tuple b);
t_tuple	mult_tuple(t_tuple a, double b);
t_tuple inverse_tuple(t_tuple a);
int	comp_tuple(t_tuple a, t_tuple b);

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
