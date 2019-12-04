/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:10:43 by gfoote            #+#    #+#             */
/*   Updated: 2019/09/30 17:10:45 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

t_ray	init_ray(t_vec origin, t_vec direction)
{
	t_ray result;

	result.origin = init_v(origin.x, origin.y, origin.z);
	result.direction = init_v(direction.x, direction.y, direction.z);
	return (result);
}

t_vec	point_to_parameter(t_ray ray, float param)
{
	return (add_v(ray.origin, v_multiply_l(ray.direction, param)));
}
