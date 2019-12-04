/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:46:59 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/22 19:47:01 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			ft_strchsymb2(const char *str, char a, int start)
{
	int i;

	i = start;
	while (str[i])
	{
		if (str[i] == a)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_check(const char *str, const char *str2, int start)
{
	int i;

	i = 0;
	while (str2[i] && str[start])
	{
		if (str[start] != str2[i])
			return (-1);
		start++;
		i++;
	}
	return (1);
}

int			ft_strstr2(const char *str, const char *needle, int start)
{
	int i;

	i = start;
	while (str[i])
	{
		if (str[i] == needle[0] && ft_check(str, needle, i) == 1)
			return (i);
		i++;
	}
	return (-1);
}

int			print_error(const char *error)
{
	ft_putendl_fd(error, 2);
	return (-1);
}

void		ft_strdel2(char **as)
{
	if (as && *as)
	{
		while (*as)
		{
			free(*as);
			as++;
		}
	}
}
