/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:21:48 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/19 15:21:49 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	closest_object(t_ray ray, double min, double max, t_map *map)
{
	t_root	ts;
	t_obj	*tmp;

	tmp = map->obj;
	map->tr.closest_obj = max;
	map->tr.near = NULL;
	while (tmp)
	{
		ts = hit_figures(ray, tmp);
		if (ts.a < map->tr.closest_obj && min < ts.a && ts.a < max)
		{
			map->tr.closest_obj = ts.a;
			map->tr.near = tmp;
		}
		if (ts.b < map->tr.closest_obj && min < ts.b && ts.b < max)
		{
			map->tr.closest_obj = ts.b;
			map->tr.near = tmp;
		}
		tmp = tmp->next;
	}
}
