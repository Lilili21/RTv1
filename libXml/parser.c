/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:35:40 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 13:30:12 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_obj(char *obj)
{
	if (ft_strequ(obj, "cone"))
		return (CONE);
	else if (ft_strequ(obj, "plane"))
		return (PLANE);
	else if (ft_strequ(obj, "sphere"))
		return (SPHERE);
	else if (ft_strequ(obj, "cylinder"))
		return (CYLINDER);
	else if (ft_strequ(obj, "camera"))
		return (CAM);
	else if (ft_strequ(obj, "light"))
		return (LIGHT);
	else if (ft_strequ(obj, "/scene"))
		return (0);
	else
		return (-1);
}

static int	check_fig1(t_pos *status, t_map *map, char *tmp, char *tmp2)
{
	status->st = ft_check_obj(map, tmp2, status->st);
	free_return(tmp, tmp2, 0);
	if (status->st == -1)
		return (-1);
	check_parsing(&status->st, &status->fin);
	return (1);
}

static int	check_fig(char *result, int i, t_map *map, t_pos *stat)
{
	t_pos	obj1;
	t_pos	obj2;
	char	*tmp;
	char	*tmp2;

	obj1.st = i + 1;
	obj1.fin = ft_strchsymb2(result, '>', obj1.st);
	if (!(tmp = ft_strsub(result, obj1.st, obj1.fin - obj1.st)))
		return (print_error("parser error: malloc error"));
	if ((stat->st = check_obj(tmp)) >= CONE && stat->st <= CAM)
	{
		if ((stat->fin == 100 && stat->st == CAM) || stat->fin % 100 == 99)
			return (free_return(tmp, NULL, 2).st);
		if ((obj2 = obj_size(result, obj1.fin, tmp, 0)).st == -1)
			return (free_return(tmp, NULL, 0).st);
		if (!(tmp2 = ft_strsub(result, obj1.fin + 1, obj2.st - obj1.fin - 3)))
			return (free_return(tmp, NULL, 3).st);
		i = check_fig1(stat, map, tmp, tmp2) + obj2.fin;
		return (i - obj2.fin < 0) ? -1 : i;
	}
	else if (stat->st == 0 && stat->fin % 100 > 0 && (stat->fin % 1000)
		/ 100 == 1 && stat->fin > 900 && result[i + 8] == '\0')
		return (free_return(tmp, NULL, 0).st + 1);
	else
		return (free_return(tmp, NULL, 1).st);
}

static char	*read_file(int fd, int buff_size)
{
	int		ret;
	char	buf[buff_size];
	char	*tmp;
	char	*result;

	if (fd < 0 || !(result = ft_strnew(1)))
	{
		print_error("parser error: couldn't read file");
		return (NULL);
	}
	while ((ret = read(fd, buf, buff_size)) > 0 && result)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(result, buf);
		free(result);
		if (!tmp)
			print_error("parser error: malloc error");
		result = tmp;
	}
	if (ft_strnequ(result, "<scene>\n", 8) == 0)
	{
		print_error("parser error: wrong scene initialization");
		return (NULL);
	}
	return (result);
}

int			parse(t_map *map, int fd, int buff_size)
{
	char	*result;
	int		i;
	t_pos	status;

	i = 8;
	status = (t_pos) {0, 0};
	if (!(result = read_file(fd, buff_size)))
		return (-1);
	while (result[i])
	{
		if (result[i] == '\n' || result[i] == '\t')
			i++;
		else if (result[i] == '<')
		{
			i = check_fig(result, i, map, &status);
			if (i == 0)
				return (free_return(result, NULL, 0).st + 1);
			else if (i == -1)
				return (free_obj_n_light(map, result, 0));
		}
		else
			return (free_obj_n_light(map, result, 1));
	}
	return (-1);
}
