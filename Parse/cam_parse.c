/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:29:47 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/20 00:00:03 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	valid_has_cam(t_world *w)
{
	if (!w->amb.has_cam)
		return (1);
	return (err(RED, "Error! Has cam already\n", RESET), 0);
}

int	cam_parse(t_world *w, char *line)
{
	int			fov;
	char		**line_split;
	t_camera	n_cam;
	t_point		cam_position;
	t_vector	cam_direction;

	line_split = my_split(line, ' ');
	if (!valid_line_count(line_split, 4)
		|| !valid_has_cam(w)
		|| !get_coords(line_split[1], &cam_position)
		|| !get_dir(line_split[2], &cam_direction)
		|| !get_int(line_split[3], &fov))
	{
		line_split = memcard(line_split, VECTOR, FREE, 0);
		return (err(RED, "Error! cam_parse ko\n", RESET), 0);
	}
	line_split = memcard(line_split, VECTOR, FREE, 0);
	if (!(fov >= 0 && fov <= 180))
		return (err(RED, "Error! fov limits ko\n", RESET), 0);
	w->amb.has_cam = 1;
	n_cam = camera(WIDTH, HEIGHT, (fov * M_PI) / 180);
	n_cam.transform = view_transform(cam_position, add_tuple(cam_position, cam_direction), vector(0, 1, 0));
	n_cam.inverse = inverse(n_cam.transform);
	w->cam = n_cam;
	return (1);
}
