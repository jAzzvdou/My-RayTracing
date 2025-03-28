/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:28:47 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:28:48 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	return (tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	return (tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}

t_tuple	mult_tuple(t_tuple a, double b)
{
	return (tuple(a.x * b, a.y * b, a.z * b, a.w * b));
}

t_tuple	inverse_tuple(t_tuple a)
{
	return (tuple(-a.x, -a.y, -a.z, -a.w));
}

int	comp_tuple(t_tuple a, t_tuple b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w)
		return (1);
	return (0);
}
