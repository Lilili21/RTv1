/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:14:20 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 13:27:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		ft_check_si(float *a, char *data)
{
	int i;
	int check_dot;

	i = -1;
	check_dot = 0;
	while (data[++i])
	{
		if ((data[i] == 'f' && i != 0 && data[i + 1] == '\0')
			|| (data[i] >= '0' && data[i] <= '9')
			|| (data[i] == '.' && check_dot == 0))
		{
			if (data[i] == '.')
				check_dot = 1;
			i++;
		}
		else
			return (print_error("parser error: wrong syntax"));
	}
	*a = atof(data);
	return (0);
}

static int		ft_parse_el(t_tmp *new, char *tmp2, int type)
{
	char	**material;
	int		check;
	int		size;

	if (!(material = ft_strsplit(tmp2, ' ')))
		return (-2);
	size = ft_size(material);
	check = 0;
	if (ft_check_el(type, size) == -1)
		check = print_error("parser error: wrong syntax");
	else if (type == TYPE || type == SPEC || type == MATERIAL)
		check = ft_parse_el2(type, material[0], new);
	else if (type == INTENS)
		check = ft_check_si(&new->intensity, material[0]);
	else if (type == POS)
		check = ft_check_pd(&new->pos, material);
	else if (type == DIR)
		check = ft_check_pd(&new->dir, material);
	else if (type == SIZE)
		check = ft_check_si(&new->size, material[0]);
	else if (type == COLOR)
		check = ft_check_c(&new->color, material);
	ft_strdel2(material);
	free(material);
	return (check < 0) ? check : type;
}

static int		ft_check_params(int type, int check, int key)
{
	if (key == 0)
	{
		if ((type == POS && check / 10 == 1)
			|| (type == DIR && (check / DIR) % 10 == 1)
			|| (type == COLOR && check / COLOR % 10 == 1)
			|| (type == SIZE && check / SIZE % 10 == 1)
			|| (type == INTENS && check / INTENS % 10 == 1)
			|| (type == TYPE && check / TYPE % 10 == 1)
			|| (type == SPEC && check / SPEC % 10 == 1)
			|| (type == MATERIAL && check / MATERIAL % 10 == 1))
			return (-1);
	}
	else
	{
		if ((type == SPHERE && check != 11001110) ||
			(type == CONE && check != 11001111) ||
			(type == PLANE && check != 11000111) ||
			(type == CYLINDER && check != 11001111))
			return (-1);
	}
	return (0);
}

static t_pos	ft_add_el(char *r, t_pos d, t_tmp *new, int type)
{
	t_pos	obj1;
	t_pos	obj2;
	char	*tmp;
	char	*tmp2;
	int		check;

	if ((obj1 = obj_size(r, d.fin, NULL, 1)).st == -1)
		return (t_pos) {print_error("parser error: wrong syntax"), -1};
	if (!(tmp = ft_strsub(r, obj1.st, obj1.fin - obj1.st)))
		return (t_pos) {print_error("parser error: malloc error"), -1};
	if ((type = ft_param(tmp, type)) == -1)
		return (t_pos) {print_error("parser error: wrong params"), -1};
	else if ((obj2 = obj_size(r, obj1.fin, tmp, 0)).fin == -1)
		return (free_return(tmp, NULL, 0));
	else if (!(tmp2 = ft_strsub(r, obj1.fin + 1, obj2.st - obj1.fin - 3)))
		return (free_return(tmp, NULL, 3));
	if (ft_check_params(type, d.st, 0) == -1)
		return (t_pos) {print_error("parser error: too much params"), -1};
	check = ft_parse_el(new, tmp2, type);
	free_return(tmp, tmp2, 0);
	if (check < 0)
		return ((t_pos){-1, -1});
	d.st = d.st + check;
	d.fin = obj2.fin + 1;
	return (d);
}

int				ft_check_obj(t_map *map, char *result, int type_str)
{
	t_pos	data;
	t_tmp	tmp;

	data = (t_pos){0, 0};
	tmp.type_str = type_str;
	while (result[data.fin])
	{
		if (result[data.fin] == '\n' || result[data.fin] == '\t')
			data.fin++;
		else if (result[data.fin] == '<')
		{
			data = ft_add_el(result, data, &tmp, tmp.type_str);
			if (data.st == -1 || data.fin == -1)
				return (-1);
		}
		else
			return (print_error("parser error: wrong syntax"));
	}
	if ((ft_check_params(type_str, data.st, 1) == -1) ||
		(type_str == LIGHT && (tmp.type < 1 || tmp.type > 2)) ||
		(type_str == LIGHT && tmp.type == 1 && data.st != 110000) ||
		(type_str == LIGHT && tmp.type == 2 && data.st != 110010))
		return (print_error("parser error : wrong params test"));
	return (ft_add_to_map(map, tmp));
}
