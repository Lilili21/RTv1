/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:26:05 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/05 16:26:06 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		convert_coords(t_vec left_corner, int x, int y)
{
	t_vec		dis;

	dis.x = ((float)x) * left_corner.x / WIDTH;
	dis.y = ((float)y) * left_corner.y / HEIGHT;
	dis.z = 1;
	return (dis);
}
