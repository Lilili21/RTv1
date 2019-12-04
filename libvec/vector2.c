/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:39:17 by gfoote            #+#    #+#             */
/*   Updated: 2019/09/30 14:39:18 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	add_v(t_vec v1, t_vec v2)
{
	return (init_v(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	sub_v(t_vec v1, t_vec v2)
{
	return (init_v(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec	multiply_v(t_vec v1, t_vec v2, int op)
{
	t_vec result;

	if (op == '/' && (v2.x == 0 || v2.y == 0 || v2.z == 0))
		return (v2);
	if (op == '*')
		result = init_v(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	else
		result = init_v(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	return (result);
}

t_vec	cross(t_vec v1, t_vec v2)
{
	t_vec result;

	result = init_v(v1.y * v2.z - v1.z * v2.y, -(v1.x * v2.z - v1.z * v2.x),
			v1.x * v2.y - v1.y * v2.x);
	return (result);
}

float	dot(t_vec v1, t_vec v2)
{
	return (SUM3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}
