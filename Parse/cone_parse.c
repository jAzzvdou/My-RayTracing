/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:35:17 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/16 17:38:18 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	cone_parse(t_world *w, char *line)
{
	t_point		p;
	t_vector	n;
	t_object	n_cn;
	char		**arr;

	printf("----------CONE PARSE----------\n");
	n_cn = new_object(CN);
	arr = my_split(line, ' ');
	if (!get_coords(arr[1], &p) || !get_dir(arr[2], &n) || !get_double(arr[3], &n_cn.radius) || !get_double(arr[4], &n_cn.maximum) || !get_color(arr[5], &n_cn.material.color))
	{
		//split free
		printf("Cone parse ko\n");
		return (0);
	}
	//split free
	n_cn.radius /= 2;
	n_cn.maximum /= 2;
	n_cn.maximum /= n_cn.radius;
	n_cn.minimum = -n_cn.maximum;
	n_cn.closed = true;
	//set_transform(&n_cn, );
	add_object(&w->object, n_cn);
	printf("Cone Parse ok\n");
	return (1);
}

