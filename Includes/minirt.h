/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:24:41 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/13 21:07:21 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//----------| LIBRARIES |----------//
# include <unistd.h>               //| WRITE, READ
# include <stdlib.h>               //| MALLOC, FREE, NULL
# include <fcntl.h>                //| OPEN, CLOSE
# include <stdio.h>                //| PRINTF
# include <limits.h>               //| INTMAX, INTMIN
# include <math.h>                 //| SIN, COS
# include "./minilibx-linux/mlx.h" //| MiniLibX
# include "memory.h"               //| MEMORYCARD

//----------| DEFINES |----------//
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
# define WIDTH  1000
# define HEIGHT 1000
//__________ errors __________
# define ARGV "Error! Usage: ./fdf <filename>.\n"
# define FILENAME "Error! File Not '.rt'.\n"

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
	e_type	type;
	double	amblight;
	double	rgb[3];
}	t_amb;

typedef struct s_cam
{
	e_type	type;
	double	coord[3];
	double	nvector[3];
	int	fov;
}	t_cam;

typedef struct s_light
{
	e_type	type;
	double	coord[3];
	double	brightness;
	double	rgb[3];
}	t_light;

typedef	struct s_plane
{
	t_type	type;
	double	coord[3];
	double	diameter;
	double	rgb[3];
}	t_plane;

typedef	struct s_cylinder
{
	t_type	type;
	double	coord[3];
	double	nvector[3];
	double	diameter;
	double	height;
	double	rgb[3];
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

//----------| CLEANERS |----------//

//----------| UTILS |----------//

#endif //| MINIRT_H
