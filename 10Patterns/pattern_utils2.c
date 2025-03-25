/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:43:12 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:45:07 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_color	stripe_at(t_pattern p, t_point pt)
{
	if ((int)floor(pt.x) % 2 == 0)
		return (p.a);
	return (p.b);
}

t_color	gradient_at(t_pattern p, t_point pt)
{
	double	fraction;
	t_color	distance;

	distance = sub_color(p.b, p.a);
	fraction = fmod(fabs(pt.x), 1);
	if (fmod(fabs(pt.x), 2) >= 1)
		fraction = 1 - fmod(fabs(pt.x), 1);
	return (add_color(mult_color(distance, fraction), p.a));
}

int	near_zero(double nb)
{
	return (nb < EPSILON && nb > -EPSILON);
}

t_color	ring_at(t_pattern p, t_point pt)
{
	double	discriminant;

	discriminant = floor(sqrt(pow(pt.x, 2) + pow(pt.z, 2)));
	if (near_zero(fmod(discriminant, 2)))
		return (p.a);
	return (p.b);
}

t_color	checker_at(t_pattern p, t_point pt)
{
	int	mod;
	int	sum;

	mod = 1;
	sum = (int)(pt.x + pt.y + pt.z);
	if (sum % 2 == 0)
		mod = 0;
	if (pt.x < 0)
		mod = !mod;
	if (pt.z < 0)
		mod = !mod;
	if (mod)
		return (p.a);
	return (p.b);
}
