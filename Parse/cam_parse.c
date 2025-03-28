/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:29:47 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:15:22 by jbergfel         ###   ########.fr       */
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
	char		**splited;
	t_camera	n_cam;
	t_point		cam_position;
	t_vector	cam_direction;

	splited = my_split(line, ' ');
	if (!valid_line_count(splited, 4) || !valid_has_cam(w)
		|| !get_coords(splited[1], &cam_position)
		|| !get_dir(splited[2], &cam_direction)
		|| !get_int(splited[3], &fov))
	{
		splited = memcard(splited, VECTOR, FREE, 0);
		return (err(RED, "Error! cam_parse ko\n", RESET), 0);
	}
	w->amb.has_cam = 1;
	splited = memcard(splited, VECTOR, FREE, 0);
	if (!(fov >= 0 && fov <= 180))
		return (err(RED, "Error! fov limits ko\n", RESET), 0);
	n_cam = camera(WIDTH, HEIGHT, (fov * M_PI) / 180);
	n_cam.transform = view_transform(cam_position,
			add_tuple(cam_position, cam_direction), vector(0, 1, 0));
	n_cam.inverse = inverse(n_cam.transform);
	w->cam = n_cam;
	return (1);
}
