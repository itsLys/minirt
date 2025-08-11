/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:04:43 by yel-guad          #+#    #+#             */
/*   Updated: 2025/08/11 14:37:17 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#define ERR ""
#define ERR_MALLOC ""

void	exit_error(char *str);
t_coords	get_coords(char **line);
t_rgb	get_color(char **line);

double	vector_len(t_coords v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}


void	init_plane(char *line, t_data *data)
{
	t_obj	*obj;
	t_pl	*pl;
	t_coords	point;  // obj
	t_rgb		color;   // obj
	t_coords	norm;

	point = get_coords(&line);
	color = get_color(&line);
	norm = get_coords(&line);
	if (color.rgba < 0 || color.rgba > 255)
		exit_error(ERR);
	if (vector_len(norm) != 1)
		exit_error(ERR);
	obj = malloc(sizeof(obj)); // s
	pl = malloc(sizeof(t_pl));
	if (!obj || !pl)
		exit_error(ERR_MALLOC);
	obj->color = color;
	obj->pos = point;
	obj->type = OBJ_PL;
	pl->norm = norm;
	obj->shape = pl;
}

void	init_sphere(char *line, t_data *data)
{
	t_obj	*obj;
	t_sp	*sp;
	t_coords	center;  // obj
	t_rgb		color;   // obj
	double		diameter;

	center = get_coords(&line);
	diameter = get_double(&line);
	color = get_color(&line);
	if (color.rgba < 0 || color.rgba > 255)
		exit_error(ERR);
	obj = malloc(sizeof(obj)); // s
	sp = malloc(sizeof(t_sp));
	if (!obj || !sp)
		exit_error(ERR_MALLOC);
	obj->color = color;
	obj->pos = center;
	obj->type = OBJ_SP;
	sp->d = diameter;
	obj->shape = sp;
}


void	init_cylinder(char *line, t_data *data)
{
	t_obj	*obj;
	t_cy	*cy;
	t_coords	center;
	t_coords	norm;
	t_rgb		color;
	double		diameter;
	double		 height;

	center = get_coords(&line);
	norm = get_coords(&line); // 
	diameter = get_double(&line);
	height = get_double(&line);
	color = get_color(&line);
	if (vector_len(norm) != 1.0) // range [-1, 1] ?
		exit_error(ERR);
	if (color.rgba < 0 || color.rgba > 255)
		exit_error(ERR);
	obj = malloc(sizeof(obj)); // s
	cy = malloc(sizeof(t_cy));
	if (!obj || !cy)
		exit_error(ERR_MALLOC);
	data->scene.objs->pos = center;
	data->scene.objs->color = color;
	data->scene.objs->type = OBJ_CY;
	cy->d = diameter;
	cy->h =  height;
	cy->norm = norm;
	data->scene.objs->shape = cy;
}

