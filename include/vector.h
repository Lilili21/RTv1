/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:23:48 by gfoote            #+#    #+#             */
/*   Updated: 2019/09/30 14:23:50 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

# define SUM3(a, b, c) a + b + c

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

typedef struct	s_ray
{
	t_vec origin;
	t_vec direction;
}				t_ray;

t_vec			init_v(float x, float y, float z);
t_vec			v_multiply_l(t_vec v1, float l);
t_vec			make_unit_v(t_vec v1);
float			length_v(t_vec v1);
t_vec			add_v(t_vec v1, t_vec v2);
t_vec			sub_v(t_vec v1, t_vec v2);
t_vec			multiply_v(t_vec v1, t_vec v2, int op);
t_ray			init_ray(t_vec origin, t_vec direction);
t_vec			point_to_parameter(t_ray ray, float param);
t_vec			cross(t_vec v1, t_vec v2);
float			dot(t_vec v1, t_vec v2);
t_vec			copy_v(t_vec copy);
#endif
