/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:33:30 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 13:27:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_check_c(t_color *color, char **data)
{
	int i;
	int j;

	i = -1;
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
		{
			if (data[i][j] < '0' || data[i][j] > '9')
				return (print_error("parser error: wrong syntax color"));
		}
	}
	color->r = ft_atoi(data[0]);
	color->g = ft_atoi(data[1]);
	color->b = ft_atoi(data[2]);
	if (color->r > 256 || color->b > 256 || color->g > 256)
		return (print_error("parser error: wrong size of color"));
	return (0);
}

int		ft_check_pd(t_vec *vec, char **data)
{
	int i;
	int j;
	int check_dot;

	i = -1;
	while (data[++i])
	{
		j = (data[i][0] == '-') ? 1 : 0;
		check_dot = 0;
		while (data[i][j])
		{
			if ((data[i][j] == 'f' && j != 0 && data[i][j + 1] == '\0'
			&& ft_isdigit(data[i][j - 1])) || (data[i][j] >= '0' && data[i][j]
			<= '9') || (data[i][j] == '.' && check_dot == 0))
			{
				if (data[i][j] == '.')
					check_dot = 1;
				j++;
			}
			else
				return (print_error("parser error: wrong syntax coordinates"));
		}
	}
	*vec = init_v(atof(data[0]), atof(data[1]), atof(data[2]));
	return (0);
}

t_pos	obj_size(char *str, int start, char *obj, int type)
{
	t_pos obj_pos;

	if (type == 1)
	{
		obj_pos.st = start + 1;
		obj_pos.fin = ft_strchsymb2(str, '>', obj_pos.st);
		if (obj_pos.fin == 0)
			return (t_pos){-1, -1};
	}
	else
	{
		obj_pos.st = ft_strstr2(str, obj, start + 1);
		obj_pos.fin = ft_strchsymb2(str, '>', obj_pos.st);
		if (str[obj_pos.st - 2] != '<' || (str[obj_pos.st - 1] != '/')
			|| (size_t)(obj_pos.fin - obj_pos.st) != ft_strlen(obj))
		{
			print_error("parser error: wrong syntax params");
			return (t_pos) {-1, -1};
		}
	}
	return (obj_pos);
}

int		ft_param(char *param, int type)
{
	if (!param)
		return (-1);
	if (ft_strequ(param, "pos"))
		return (POS);
	if (type == LIGHT)
	{
		if (ft_strequ(param, "intensity"))
			return (INTENS);
		if (ft_strequ(param, "type"))
			return (TYPE);
	}
	else if (type != CAM)
	{
		if (ft_strequ(param, "dir"))
			return (DIR);
		if (ft_strequ(param, "color"))
			return (COLOR);
		if (ft_strequ(param, "size"))
			return (SIZE);
		if (ft_strequ(param, "spec"))
			return (SPEC);
		if (ft_strequ(param, "material"))
			return (MATERIAL);
	}
	return (-1);
}

int		ft_size(char **size)
{
	int i;

	i = 0;
	while (size[i])
		i++;
	return (i);
}
