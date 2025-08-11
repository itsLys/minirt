/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 16:52:42 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_source_light(char *line, t_data *data)
{
	t_obj			*obj;
	t_light_src		*source;
	t_coords		pos;
	double			ratio;
	t_rgb			rgba;

	pos = get_vec3(&line);
	ratio = get_double(&line);
	rgba = get_rgba(&line);
	obj = malloc(sizeof(t_obj));
	source = malloc(sizeof(t_light_src));
	if (obj == NULL || source == NULL)
		exit_error(NULL);
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_LIGHT ERR_RATIO);
	if ((int) rgba.a == ERROR)
		exit_error(ERR_LIGHT ERR_RGB);
	obj->type = T_LS;
	obj->pos = pos;
	obj->color = rgba;
	source->ratio = ratio;
	// obj_list_add ( source);
}

void	init_plane(char *line, t_data *data)
{
	t_obj	*obj;
	t_pl	*pl;
	t_coords	point;  // obj
	t_rgb		color;   // obj
	t_coords	norm;

	point = get_vec3(&line);
	color = get_rgba(&line);
	norm = get_vec3(&line);
	if (vec3_len(norm) != 1)
		exit_error(ERR_PL ERR_NORM_VAL);
	obj = malloc(sizeof(t_obj)); // s
	pl = malloc(sizeof(t_pl));
	if (!obj || !pl)
		exit_error(NULL);
	obj->color = color;
	obj->pos = point;
	obj->type = T_PL;
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

	center = get_vec3(&line);
	diameter = get_double(&line);
	color = get_rgba(&line);
	obj = malloc(sizeof(t_obj)); // s
	sp = malloc(sizeof(t_sp));
	if (!obj || !sp)
		exit_error(NULL);
	obj->color = color;
	obj->pos = center;
	obj->type = T_SP;
	sp->d = diameter;
	obj->shape = sp;
}

void	init_cylinder(char *line, t_data *data)
{
	t_obj		*obj;
	t_cy		*cy;

	cy  = malloc(sizeof(t_cy));
	obj = malloc(sizeof(t_obj));
	if (obj == NULL || cy == NULL)
		return free(cy), exit_error(NULL);
	obj->shape = cy;
	// obj list add (obj)
	obj->pos = get_vec3(&line);
	cy->norm = get_vec3(&line);
	if (vec3_len(cy->norm) != 1.0) // range [-1, 1] ?
		exit_error(ERR_CY ERR_NORM_VAL);
	cy->d = get_double(&line);
	cy->h = get_double(&line);
	obj->color = get_rgba(&line);
}
