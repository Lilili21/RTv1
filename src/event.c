/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:13:43 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 14:33:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			event(t_sdl sdl)
{
	while (1)
	{
		while (SDL_PollEvent(&sdl.event))
			if ((SDL_QUIT == sdl.event.type) ||
				(SDL_KEYDOWN == sdl.event.type &&
				SDL_SCANCODE_ESCAPE == sdl.event.key.keysym.scancode))
			{
				SDL_DestroyTexture(sdl.buff_texture);
				SDL_DestroyRenderer(sdl.ren);
				SDL_DestroyWindow(sdl.window);
				SDL_Quit();
				exit(0);
			}
	}
}
