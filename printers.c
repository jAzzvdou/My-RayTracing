/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:25 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 13:49:46 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minirt.h"

void	print_type(t_type type)
{
	if (type == A)
		printf("Type: A.\n");
	else if (type == C)
		printf("Type: C.\n");
	else if (type == L)
		printf("Type: L.\n");
	else if (type == SP)
		printf("Type: SP.\n");
	else if (type == PL)
		printf("Type: PL.\n");
	else if (type == CY)
		printf("Type: CY.\n");
	else
		printf("Type: NONE.\n");
}

void	print_rgb(int *rgb)
{
	printf("Red: %d | ", rgb[0]);
	printf("Green: %d | ", rgb[1]);
	printf("Blue: %d |\n", rgb[2]);
}

void	print_coord(double *coord)
{
	printf("Coord X: %lf | ", coord[0]);
	printf("Coord Y: %lf | ", coord[1]);
	printf("Coord Z: %lf |\n", coord[2]);
}

void	print_nvector(double *nvector)
{
	printf("vector X: %lf | ", nvector[0]);
	printf("Vector Y: %lf | ", nvector[1]);
	printf("Vector Z: %lf |\n", nvector[2]);
}

void	print_amb(t_amb *amb)
{
	print_type(amb->type);
	printf("Amblight: %lf.\n", amb->amblight);
	print_rgb(amb->rgb);
	printf("\n");
}

void	print_cam(t_cam *cam)
{
	print_type(cam->type);
	print_coord(cam->coord);
	print_nvector(cam->nvector);
	printf("FOV: %d.\n", cam->fov);
	printf("\n");
}

void	print_light(t_light *light)
{
	print_type(light->type);
	print_coord(light->coord);
	printf("Brightness: %lf.\n", light->brightness);
	print_rgb(light->rgb);
	printf("\n");
}

void	print_sphere(t_sphere *sphere)
{
	print_type(sphere->type);
	print_coord(sphere->coord);
	printf("Diameter: %lf.\n", sphere->diameter);
	print_rgb(sphere->rgb);
	printf("\n");
}

void	print_plane(t_plane *plane)
{
	print_type(plane->type);
	print_coord(plane->coord);
	print_nvector(plane->nvector);
	print_rgb(plane->rgb);
	printf("\n");
}

void	print_cylinder(t_cylinder *cylinder)
{
	print_type(cylinder->type);
	print_coord(cylinder->coord);
	print_nvector(cylinder->nvector);
	printf("Diameter: %lf.\n", cylinder->diameter);
	printf("Height: %lf.\n", cylinder->height);
	print_rgb(cylinder->rgb);
	printf("\n");
}

void	print_map(t_map *map)
{
	if (map->a)
		print_amb(map->a);
	if (map->c)
		print_cam(map->c);
	if (map->l)
		print_light(map->l);
	if (map->sp)
		print_sphere(map->sp);
	if (map->pl)
		print_plane(map->pl);
	if (map->cy)
		print_cylinder(map->cy);
}
