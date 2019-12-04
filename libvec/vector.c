/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 13:47:40 by gfoote            #+#    #+#             */
/*   Updated: 2019/09/30 13:47:42 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	init_v(float x, float y, float z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec	v_multiply_l(t_vec v1, float l)
{
	return (init_v(v1.x * l, v1.y * l, v1.z * l));
}

float	length_v(t_vec v1)
{
	return ((float)sqrt(SUM3(pow(v1.x, 2), pow(v1.y, 2), pow(v1.z, 2))));
}

t_vec	make_unit_v(t_vec v1)
{
	t_vec result;
	float k;

	if (v1.x == 0 && v1.y == 0 && v1.z == 0)
		return (v1);
	k = (float)(1.0 / (length_v(v1)));
	result = v_multiply_l(v1, k);
	return (result);
}

t_vec	copy_v(t_vec copy)
{
	t_vec result;

	result.x = copy.x;
	result.y = copy.y;
	result.z = copy.z;
	return (result);
}
