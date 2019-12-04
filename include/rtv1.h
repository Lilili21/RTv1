/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:18:18 by gfoote            #+#    #+#             */
/*   Updated: 2019/09/26 15:18:23 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "vector.h"
# include "parser.h"

# define WIDTH 600
# define HEIGHT 600

int			init(t_map *map);
void		draw(t_map *map);
void		draw_buff(t_map *map);
t_vec		convert_coords(t_vec left_corner, int x, int y);
void		closest_object(t_ray ray, double min, double max, t_map *map);
t_root		hit_figures(t_ray ray, t_obj *obj);
int			color_parse(t_color col, double c);
t_vec		get_normal(t_obj *obj, t_vec point);
double		lightning(t_map *map, t_vec point, t_ray ray_nv, double spec);
int			event(t_sdl sdl);
#endif
