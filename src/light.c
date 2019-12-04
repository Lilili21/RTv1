/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:31:51 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/08 14:31:53 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	f_intens(t_vec prms, t_ray ray_lr, t_ray ray_nv)
{
	double	n_dot_l;
	double	r_dot_v;
	float	intens;

	intens = prms.y;
	n_dot_l = dot(ray_nv.origin, ray_lr.origin);
	if (n_dot_l > 0)
		intens += (float)(prms.x * n_dot_l / (length_v(ray_nv.origin)
			* length_v(ray_lr.origin)));
	if (prms.z >= 0)
	{
		ray_lr.direction = sub_v((v_multiply_l(ray_nv.origin, 2.0f *
		dot(ray_nv.origin, ray_lr.origin))), ray_lr.origin);
		r_dot_v = dot(ray_lr.direction, ray_nv.direction);
		if (r_dot_v > 0)
			intens += (float)(prms.x * pow(r_dot_v / (length_v(ray_lr.direction)
			* length_v(ray_nv.direction)), prms.z));
	}
	return (intens);
}

void	closest_object_light(t_ray ray, double min, double max, t_map *map)
{
	t_root	ts;
	t_obj	*tmp;

	tmp = map->obj;
	map->tr.closest_obj2 = max;
	map->tr.near2 = NULL;
	while (tmp)
	{
		ts = hit_figures(ray, tmp);
		if (ts.a < map->tr.closest_obj2 && min < ts.a && ts.a < max)
		{
			map->tr.closest_obj2 = ts.a;
			map->tr.near2 = tmp;
		}
		if (ts.b < map->tr.closest_obj2 && min < ts.b && ts.b < max)
		{
			map->tr.closest_obj2 = ts.b;
			map->tr.near2 = tmp;
		}
		tmp = tmp->next;
	}
}

double	lightning(t_map *map, t_vec point, t_ray ray_nv, double spec)
{
	float	intens;
	t_ray	ray_lr;
	t_ray	ray;
	t_light *tmp;

	intens = 0.0f;
	tmp = map->light;
	while (tmp)
	{
		if (tmp->type == AMBIENT)
			intens += tmp->intensity;
		else if (tmp->type == POINT)
		{
			ray_lr.origin = sub_v(tmp->pos, point);
			ray = init_ray(point, ray_lr.origin);
			closest_object_light(ray, 0.0001f, 0.9f, map);
			if (map->tr.near2 == NULL && map->tr.closest_obj2 == 0.9f)
				intens = f_intens((t_vec){tmp->intensity, intens, (float)spec},
						ray_lr, ray_nv);
		}
		tmp = tmp->next;
	}
	intens > 1.0 ? intens = 1.0f : 0;
	return (intens);
}
