/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:38:49 by gfoote            #+#    #+#             */
/*   Updated: 2019/10/29 12:38:51 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init(t_map *map)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (print_error(SDL_GetError()));
	if (!(map->sdl.window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL)))
		return (print_error(SDL_GetError()));
	map->sdl.ren = SDL_CreateRenderer(map->sdl.window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	map->sdl.buff_texture =
			SDL_CreateTexture(map->sdl.ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	if (map->sdl.buff_texture == NULL)
		return (print_error(SDL_GetError()));
	if (!(map->buff = ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		return (print_error("RTv1: Cannot allocate memory."));
	return (0);
}
