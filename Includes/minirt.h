/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:24:41 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/17 11:59:36 by jazevedo         ###   ########.fr       */
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
# include <math.h>                    //| SIN, COS
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
# define WIDTH  1920
# define HEIGHT 1080
//__________ errors __________
# define ARGV "Error! Usage: ./miniRT <filename>.\n"
# define FILENAME "Error! File Is Not '.rt'.\n"
# define INVALID_FILE "Error! Invalid File.\n"
# define INVALID_VARIABLE "Error! Invalid Element Name.\n"
//__________ types __________
# define INT 2147483647
# define DOUBLE 179769308

//----------| STRUCTS |----------//
typedef enum e_type
{
	A,
	C,
	L,
	PL,
	SP,
	CY
}	t_type;

typedef struct s_amb
{
	t_type	type;
	double	amblight;
	int	rgb[3];
}	t_amb;

typedef struct s_cam
{
	t_type	type;
	double	coord[3];
	double	nvector[3];
	int	fov;
}	t_cam;

typedef struct s_light
{
	t_type	type;
	double	coord[3];
	double	brightness;
	int	rgb[3];
}	t_light;

typedef	struct s_sphere
{
	t_type	type;
	double	coord[3];
	double	diameter;
	int	rgb[3];
}	t_sphere;

typedef	struct s_plane
{
	t_type	type;
	double	coord[3];
	double	diameter;
	int	rgb[3];
}	t_plane;

typedef	struct s_cylinder
{
	t_type	type;
	double	coord[3];
	double	nvector[3];
	double	diameter;
	double	height;
	int	rgb[3];
}	t_cylinder;

typedef struct s_map
{
	t_amb		*a;
	t_cam		*c;
	t_light		*l;
	t_plane		*pl;
	t_sphere	*sp;
	t_cylinder	*cy;
}	t_map;

typedef struct s_minilibx
{
	int	bpp;
	int	linelen;
	int	endian;
	char	*addr;
	void	*mlx;
	void	*win;
	void	*img;
}	t_minilibx;

typedef struct s_main
{
	t_map		*map;
	t_minilibx	*libx;
}	t_main;

//----------| FUNCTIONS |----------//
//__________ parser __________
int	invalid_rgb(char *line);
int	invalid_coord(char *line);
int	add_ambient(t_map *map, char *line);
int	add_camera(t_map *map, char *line);
t_map	*readfile(char *file);
//__________ screen __________
void	screen(t_minilibx *libx);

//----------| ERRORS |----------//
void	err(char *color1, char *error, char *color2);

//----------| CLEANERS |----------//

//----------| UTILS |----------//
//__________ space.c __________
void	skip_spaces(char **s);
//__________ splitline.c __________
char	**splitline(char const *s, char c);
//__________ get_next_line.c __________
char	*get_next_line(int fd);
//__________ lib1.c __________
size_t	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	revstrncmp(char *s1, char *s2, int n);
char	*ft_strchr(const char *s, int c);
//__________ lib2.c __________
char	*ft_strjoin(char *s1, char *s2);
//__________ lib3.c __________
size_t	matrixlen(char **matrix);
int	ft_atoi(const char *nptr);
double	ft_atod(const char *nptr);
//__________ lib4.c __________
int	ft_isdigit(int c);
int	is_int(char *s);
int	is_double(char *s);
int	onlynumber(char *s, int type);

#endif //| MINIRT_H
