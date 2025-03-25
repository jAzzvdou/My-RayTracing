/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:17:26 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 12:20:06 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	get_transparency(char *s, double *transparency)
{
	*transparency = my_atod(s);
	if (*transparency < 0 || *transparency > 1)
		return (0);
	return (1);
}

int	get_reflective(char *s1, char *s2, double *reflec, double *refrac_index)
{
	*reflec = my_atod(s1);
	*refrac_index = my_atod(s2);
	if (*reflec < 0 || *reflec > 1
		|| *refrac_index < 0 || *refrac_index > 20)
		return (0);
	return (1);
}
