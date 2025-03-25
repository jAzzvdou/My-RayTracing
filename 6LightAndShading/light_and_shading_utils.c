/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_shading_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:14:28 by jbergfel          #+#    #+#             */
/*   Updated: 2025/03/25 13:14:39 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_vector	reflect(t_vector in, t_vector normal)
{
	return (sub_tuple(in, mult_tuple(normal, 2 * dot(in, normal))));
}
