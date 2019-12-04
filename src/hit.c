/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:51:21 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/08 13:51:24 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_root	hit_sphere(t_ray ray, t_obj *sphere)
{
	t_root	d;
	float	discrim;
	t_vec	oc;
	t_vec	res;

	oc = sub_v(ray.origin, sphere->pos);
	res.x = dot(ray.direction, ray.direction);
	res.y = 2.0f * dot(oc, ray.direction);
	res.z = dot(oc, oc) - sphere->size * sphere->size;
	discrim = res.y * res.y - (4.0f * res.x * res.z);
	if (discrim < 0)
		return ((t_root){-1, -1});
	d.a = ((-res.y + sqrtf(discrim)) / (2.0 * res.x));
	d.b = ((-res.y - sqrtf(discrim)) / (2.0 * res.x));
	return (d);
}

t_root	hit_plane(t_ray ray, t_obj *plane)
{
	t_root k;

	k = (t_root){-1, -1};
	if (plane->dir.x != 0 || plane->dir.y != 0 || plane->dir.z != 0)
		k.a = dot(plane->dir, sub_v(plane->pos, ray.origin)) /
			dot(plane->dir, ray.direction);
	k.b = -1.0;
	return (k);
}

t_root	hit_cylinder(t_ray ray, t_obj *cylinder)
{
	t_vec	res;
	double	discrim;
	t_root	d;

	res.x = dot(ray.direction, ray.direction) -
			(float)pow(dot(ray.direction, cylinder->dir), 2.0);
	res.y = (dot(ray.direction, sub_v(ray.origin, cylinder->pos)) -
			dot(ray.direction, cylinder->dir) *
			dot(sub_v(ray.origin, cylinder->pos), cylinder->dir)) * 2.0f;
	res.z = dot(sub_v(ray.origin, cylinder->pos), sub_v(ray.origin,
			cylinder->pos)) - (float)pow(dot(sub_v(ray.origin, cylinder->pos),
					cylinder->dir), 2) -
			(cylinder->size * cylinder->size);
	discrim = res.y * res.y - (4.0 * res.x * res.z);
	if (discrim < 0)
		return ((t_root){-1, -1});
	d.a = ((-res.y + sqrt(discrim)) / (2.0 * res.x));
	d.b = ((-res.y - sqrt(discrim)) / (2.0 * res.x));
	return (d);
}

t_root	hit_cone(t_ray ray, t_obj *cone)
{
	t_vec	res;
	float	discrim;
	t_root	d;
	float	k;

	k = 1 + cone->size * cone->size;
	res.x = dot(ray.direction, ray.direction) -
			k * (float)pow(dot(ray.direction, cone->dir), 2.0);
	res.y = 2 * (dot(ray.direction, sub_v(ray.origin, cone->pos)) -
			k * dot(ray.direction, cone->dir) *
			dot(sub_v(ray.origin, cone->pos), cone->dir));
	res.z = dot(sub_v(ray.origin, cone->pos), sub_v(ray.origin, cone->pos)) -
			k * (float)pow(dot(sub_v(ray.origin, cone->pos), cone->dir), 2);
	discrim = res.y * res.y - (4.0f * res.x * res.z);
	if (discrim < 0)
	{
		return (t_root){-1, -1};
	}
	d.a = ((-res.y + sqrtf(discrim)) / (2.0 * res.x));
	d.b = ((-res.y - sqrtf(discrim)) / (2.0 * res.x));
	return (d);
}

t_root	hit_figures(t_ray ray, t_obj *obj)
{
	if (obj->name == SPHERE)
		return (hit_sphere(ray, obj));
	else if (obj->name == PLANE)
		return (hit_plane(ray, obj));
	else if (obj->name == CONE)
		return (hit_cone(ray, obj));
	else if (obj->name == CYLINDER)
		return (hit_cylinder(ray, obj));
	return ((t_root){-1.0, -1.0});
}
