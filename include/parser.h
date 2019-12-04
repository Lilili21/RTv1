/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:10:33 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/02 13:27:40 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "vector.h"
# include "structures.h"

int		ft_strstr2(const char *str, const char *needle, int start);
int		ft_strchsymb2(const char *str, char a, int start);
int		print_error(const char *error);
void	ft_strdel2(char **as);
t_pos	free_return(char *tmp, char *tmp2, int error);
int		free_obj_n_light(t_map *map, char *result, int error);
int		ft_add_to_map(t_map *map, t_tmp	tmp);
int		ft_check_obj(t_map *map, char *result, int type_str);
int		ft_check_pd(t_vec *vec, char **data);
int		ft_check_c(t_color *color, char **data);
t_pos	obj_size(char *str, int start, char *obj, int type);
int		ft_param(char *param, int type);
int		ft_size(char **size);
int		parse(t_map *map, int fd, int buff_size);
void	check_parsing(int *a, int *b);
int		ft_check_el(int type, int size);
int		ft_parse_el2(int type, char *material, t_tmp *new);
#endif
