/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:29:47 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/15 14:41:23 by jbergfel         ###   ########.fr       */
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
	//int			fov;

	line_split = my_split(line, ' ');
	if (!valid_line_count(line_split, 4) || !valid_has_cam(w) || !get_coords(line_split[1], &cam_position) || !get_directions(line_split[2], &cam_direction))
	{
		printf("cam_parse ko\n");
		//free split
		return (0);
	}
	//free split
	w->amb.has_cam = 1;
	n_cam.transform = view_transform(cam_position, add_tuple(cam_position, cam_direction), vector(0, 1, 0));
	(void) n_cam;
	printf("cam_parse ok\n");
	return (1);
}
