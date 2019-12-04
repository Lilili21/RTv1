/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:56:35 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/15 15:56:37 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pos		free_return(char *tmp, char *tmp2, int error)
{
	if (tmp != NULL)
		free(tmp);
	if (tmp2 != NULL)
		free(tmp2);
	if (error == 1)
		print_error("parser error : wrong syntax in scene");
	else if (error == 2)
		print_error("parser error : too much objects in scene");
	else if (error == 3)
		print_error("parser error: malloc error");
	return (t_pos){-1, -1};
}

int			free_obj_n_light(t_map *map, char *result, int error)
{
	t_obj	*tmp_o;
	t_obj	*next_o;
	t_light	*tmp_l;
	t_light	*next_l;

	tmp_o = map->obj;
	while (map->count_obj > 0 && tmp_o)
	{
		next_o = tmp_o->next;
		free(tmp_o);
		tmp_o = next_o;
	}
	map->obj = NULL;
	tmp_l = map->light;
	while (map->count_light > 0 && tmp_l)
	{
		next_l = tmp_l->next;
		free(tmp_l);
		tmp_l = next_l;
	}
	map->light = NULL;
	free(result);
	return (error == 1) ? print_error("parser error: wrong syntax in scene")
	: -1;
}

static int	ft_add_figure(t_map *map, t_tmp tmp)
{
	t_obj	*new_o;
	t_obj	*tmp_o;

	if (!(new_o = (t_obj *)malloc(sizeof(t_obj))))
		return (print_error("parser error: malloc error"));
	new_o->name = tmp.type_str;
	new_o->color = (t_color) {tmp.color.r, tmp.color.g, tmp.color.b};
	new_o->pos = copy_v(tmp.pos);
	new_o->dir = (tmp.type_str == SPHERE) ? init_v(0, 0, 0) :
			make_unit_v(tmp.dir);
	new_o->size = (tmp.type_str == PLANE) ? 0 : tmp.size;
	new_o->spec = tmp.spec;
	new_o->material = tmp.material;
	new_o->next = NULL;
	tmp_o = map->obj;
	if (map->count_obj == 0)
		map->obj = new_o;
	else
	{
		while (tmp_o->next != NULL)
			tmp_o = tmp_o->next;
		tmp_o->next = new_o;
	}
	map->count_obj++;
	return (tmp.type_str);
}

static int	ft_add_light(t_map *map, t_tmp tmp)
{
	t_light	*new_l;
	t_light *tmp_l;

	if (!(new_l = (t_light *)malloc(sizeof(t_light))))
		return (print_error("parser error: malloc error"));
	new_l->type = tmp.type;
	new_l->pos = (tmp.type == AMBIENT) ? init_v(0, 0, 0) : copy_v(tmp.pos);
	new_l->intensity = tmp.intensity;
	new_l->next = NULL;
	tmp_l = map->light;
	if (map->count_light == 0)
		map->light = new_l;
	else
	{
		while (tmp_l->next != NULL)
			tmp_l = tmp_l->next;
		tmp_l->next = new_l;
	}
	map->count_light++;
	return (LIGHT);
}

int			ft_add_to_map(t_map *map, t_tmp tmp)
{
	if (tmp.type_str == CAM)
	{
		map->cam = copy_v(tmp.pos);
		return (CAM);
	}
	else if (tmp.type_str != LIGHT)
		return (ft_add_figure(map, tmp));
	else
		return (ft_add_light(map, tmp));
}
