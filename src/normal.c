/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:26:01 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/08 14:26:02 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	sphere_normal(t_obj *obj, t_vec point)
{
	t_vec normal;

	normal = sub_v(point, obj->pos);
	normal = v_multiply_l(normal, 1.0f / length_v(normal));
	return (normal);
}

t_vec	plane_normal(t_obj *obj)
{
	return (make_unit_v(obj->dir));
}

t_vec	cone_normal(t_obj *obj, t_vec point)
{
	t_vec	normal;
	double	m;
	double	k;

	k = (1 + obj->size * obj->size);
	m = dot(sub_v(point, obj->pos), obj->dir);
	normal = v_multiply_l(make_unit_v(obj->dir), (float)(m * k));
	normal = make_unit_v(sub_v(sub_v(point, obj->pos), normal));
	return (normal);
}

t_vec	cylinder_normal(t_obj *obj, t_vec point)
{
	t_vec	normal;
	double	m;

	m = dot(sub_v(point, obj->pos), obj->dir);
	normal = v_multiply_l(make_unit_v(obj->dir), (float)m);
	normal = make_unit_v(sub_v(sub_v(point, obj->pos), normal));
	return (normal);
}

t_vec	get_normal(t_obj *obj, t_vec point)
{
	if (obj->name == SPHERE)
		return (sphere_normal(obj, point));
	else if (obj->name == PLANE)
		return (plane_normal(obj));
	else if (obj->name == CONE)
		return (cone_normal(obj, point));
	else if (obj->name == CYLINDER)
		return (cylinder_normal(obj, point));
	return ((t_vec){0.0f, 0.0f, 0.0f});
}
