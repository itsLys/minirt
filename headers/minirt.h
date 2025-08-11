/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/10 16:08:46 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

// # define MAX_OBJECT 99
typedef enum s_obj_type
{
	OBJ_SP,
	OBJ_PL,
	OBJ_CY,
}	t_obj_type;

typedef	struct s_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_light
{
	double	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_cam
{
	t_coords	pos;
	t_coords	norm;
	int			fov;
}	t_cam;

typedef struct s_light_source
{
	t_coords	pos;
	t_light		light;
}	t_light_source;

typedef struct s_sp
{
	double		d;
}	t_sp;

typedef struct s_pl
{
	t_coords	norm;
}	t_pl;

typedef struct s_cy
{
	t_coords	norm;
	double		d;
	double		h;
}	t_cy;

typedef struct s_obj
{
	t_obj_type	type;
	t_coords	pos;
	t_rgb		color;
	void		*shape;
}	t_obj;

typedef struct s_scene
{
	t_light_source *lights;
	t_light			amb_light;
	t_cam			cam;
	t_obj			*objs;
}	t_scene;

typedef struct s_data
{
	t_scene scene;
}	t_data ;

#endif
