/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:01:00 by gfoote            #+#    #+#             */
/*   Updated: 2019/11/29 16:01:02 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <math.h>
# include <fcntl.h>
# include <SDL.h>
# include <SDL_image.h>

# define AMBIENT 1
# define POINT 2

# define CONE 1
# define PLANE 2
# define SPHERE 3
# define CYLINDER 4
# define LIGHT 5
# define CAM 6

# define DIR 1
# define POS 10
# define COLOR 100
# define SIZE 1000
# define TYPE 10000
# define INTENS 100000
# define SPEC 1000000
# define MATERIAL 10000000

typedef struct		s_pos
{
	int				st;
	int				fin;
}					t_pos;

typedef struct		s_root
{
	double			a;
	double			b;
}					t_root;

typedef struct		s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct		s_obj
{
	t_vec			pos;
	t_vec			dir;
	float			size;
	t_color			color;
	int				spec;
	int				material;
	int				name;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_light
{
	int				type;
	float			intensity;
	t_vec			pos;
	struct s_light	*next;
}					t_light;

typedef struct		s_trace
{
	double			closest_obj;
	t_obj			*near;
	double			closest_obj2;
	t_obj			*near2;
}					t_trace;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*ren;
	SDL_Texture		*buff_texture;
}					t_sdl;

typedef struct		s_map
{
	t_sdl			sdl;
	unsigned int	*buff;
	t_vec			cam;
	t_trace			tr;
	t_obj			*obj;
	t_light			*light;
	int				count_obj;
	int				count_light;
}					t_map;

typedef struct		s_tmp
{
	int				type_str;
	int				name;
	int				type;
	float			intensity;
	t_vec			pos;
	t_vec			dir;
	float			size;
	t_color			color;
	int				spec;
	int				material;
}					t_tmp;

#endif
