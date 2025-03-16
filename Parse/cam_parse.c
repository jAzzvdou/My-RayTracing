/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:29:47 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 11:58:50 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	valid_has_cam(t_world *w)
{
	if (w->amb.has_cam != 0)
	{
		printf("HAS CAM ALREADY\n");
		return (0);
	}
	return (1);
}

int	cam_parse(t_world *w, char *line)
{
	char		**line_split;
	t_camera	n_cam;
	t_point		cam_position;
	t_vector	cam_direction;
	int			fov;

	printf("----------CAM PARSE----------\n");
	line_split = my_split(line, ' ');
	if (!valid_line_count(line_split, 4) || !valid_has_cam(w) || !get_coords(line_split[1], &cam_position) || !get_directions(line_split[2], &cam_direction) || !get_int(line_split[3], &fov))
	{
		printf("cam_parse ko\n");
		//free split
		return (0);
	}
	if (!(fov >= 0 && fov <= 180))
		return (printf("fov limits ko %i\n", fov), 0);
	//free split
	w->amb.has_cam = 1;
	n_cam = camera(WIDTH, HEIGHT, (fov * M_PI) / 180);
	n_cam.transform = view_transform(cam_position, add_tuple(cam_position, cam_direction), vector(0, 1, 0));
	n_cam.inverse = inverse(n_cam.transform);
	w->cam = &n_cam;
	printf("-- Cam Transform MATRIX --\n");
	print_matrix(w->cam->transform);
	printf("--                      --\n");
	printf("--  Cam INVERSE MATRIX  --\n");
	print_matrix(w->cam->inverse);
	printf("--                      --\n");
	printf("FOV-> %f\n", w->cam->fov);
	printf("cam_parse ok\n\n");
	return (1);
}
