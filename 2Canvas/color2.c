/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:51:31 by jbergfel          #+#    #+#             */
/*   Updated: 2025/02/02 19:51:54 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_color convert_color(t_color a)
{
	return (color(a.r / 255, a.g / 255, a.b / 255));
}

int	color_to_int(t_color a)
{
	int	r;
	int	g;
	int	b;

	r = (int)(a.r * 255.999);
	g = (int)(a.g * 255.999);
	b = (int)(a.b * 255.999);
	return (r << 16 | g << 8 | b);
}
