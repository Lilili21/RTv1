/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:29:17 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/08 14:29:19 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	clamp(double a)
{
	if (a <= 0)
		return (0);
	else if (a > 255)
		return (255);
	return ((int)a);
}

int	color_parse(t_color col, double c)
{
	int r;
	int g;
	int b;
	int	color;

	r = clamp((col.r & 0xFF) * c);
	g = clamp((col.g & 0xFF) * c);
	b = clamp((col.b & 0xFF) * c);
	color = (r << 16 | g << 8 | b);
	return (color);
}
