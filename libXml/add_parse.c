/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:58:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/12/02 13:27:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_check_material(char *material)
{
	size_t	i;

	i = 0;
	if (!material)
		return (print_error("parser error: material is NULL"));
	while (material[i])
	{
		if (ft_isdigit(material[i]))
			i++;
		else
			return (print_error("parser error: wrong symbols in material"));
	}
	if (i != ft_strlen(material))
		return (print_error("parser error: wrong symbols in material"));
	return (0);
}

void		check_parsing(int *a, int *b)
{
	if (*a == CAM)
		*b += 100;
	else if (*a == LIGHT)
		*b += 1000;
	else
		*b += 1;
}

static int	ft_check_stm(int *result, char *data, int type)
{
	*result = ft_atoi(data);
	if (type == 1)
	{
		if (*result == 1 || *result == 2)
			return (0);
		return (print_error("parser error: wrong type"));
	}
	if (type == 2)
		return ((*result > 0) ? 0 : print_error("parser error: wrong spec"));
	if (type == 3)
		return (ft_check_material(data));
	return (-1);
}

int			ft_check_el(int type, int size)
{
	if (((size != 1) && (type == SIZE || type == TYPE || type == INTENS ||
	type == SPEC || type == MATERIAL)) || ((size != 3) && (type == POS ||
	type == COLOR || type == DIR)))
		return (-1);
	return (0);
}

int			ft_parse_el2(int type, char *material, t_tmp *new)
{
	int check;

	check = 0;
	if (type == TYPE)
		check = ft_check_stm(&new->type, material, 1);
	else if (type == SPEC)
		check = ft_check_stm(&new->spec, material, 2);
	else
		check = ft_check_stm(&new->material, material, 3);
	return (check);
}
