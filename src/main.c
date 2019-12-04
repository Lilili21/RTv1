/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:28:17 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 12:32:18 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	map.count_obj = 0;
	map.count_light = 0;
	if (argc != 2)
		return (print_error("usage: choose RTv1 scene"));
	if (!(fd = open(argv[1], O_RDONLY)))
		return (print_error("error couldn't open scene file"));
	if (parse(&map, fd, 10) == -1)
	{
		close(fd);
		exit(-1);
	}
	if (init(&map) == -1)
		return (0);
	close(fd);
	draw(&map);
	draw_buff(&map);
	event(map.sdl);
}
