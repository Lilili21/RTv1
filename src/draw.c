/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:45:18 by gfoote            #+#    #+#             */
/*   Updated: 2019/10/29 16:45:20 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_buff(t_map *map)
{
	SDL_RenderClear(map->sdl.ren);
	SDL_UpdateTexture(map->sdl.buff_texture, NULL, map->buff,
			WIDTH * sizeof(int));
	SDL_RenderCopy(map->sdl.ren, map->sdl.buff_texture, NULL, NULL);
	SDL_RenderPresent(map->sdl.ren);
}

void	put_data(unsigned int *data, int x, int y, int color)
{
	long int cur_i;

	cur_i = x + y * (WIDTH);
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0
		&& cur_i >= 0 && cur_i < WIDTH * HEIGHT)
		data[cur_i] = color;
}

int		ray_tracer_figures(t_ray ray, double min, double max, t_map *map)
{
	t_vec	point;
	t_ray	ray_nv;
	double	fg;

	map->tr.closest_obj = max;
	closest_object(ray, min, max, map);
	if (map->tr.closest_obj == max || map->tr.near == NULL)
		return (0);
	point = add_v(ray.origin, v_multiply_l(ray.direction,
			(float)map->tr.closest_obj));
	ray_nv.origin = get_normal(map->tr.near, point);
	ray_nv.direction = v_multiply_l(ray.direction, -1.0f);
	fg = lightning(map, point, ray_nv, map->tr.near->spec);
	return ((color_parse(map->tr.near->color, fg)));
}

void	draw(t_map *map)
{
	int		color;
	int		x;
	int		y;
	t_vec	left_corner;
	t_ray	ray;

	left_corner = init_v(-1, -1, 3);
	ray.origin = copy_v(map->cam);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.direction = convert_coords(left_corner, WIDTH / 2 - x,
					y - HEIGHT / 2);
			color = ray_tracer_figures(ray, 0.0001f, 1000000.0, map);
			put_data(map->buff, x, y, color);
			x++;
		}
		y++;
	}
}
