/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 11:38:22 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void	parse_plane(char *line, t_data *data)
{
	t_obj	*obj;
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	obj = malloc(sizeof(t_obj));
	if (!obj || !pl)
		return (free(pl), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->shape = pl;
	obj->type = T_PL;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

// FIX: add a forward and up direction axis
void	parse_sphere(char *line, t_data *data)
{
	t_obj	*obj;
	t_sp	*sp;

	sp = malloc(sizeof(t_sp));
	obj = malloc(sizeof(t_obj));
	if (!obj || !sp)
		return (free(sp), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->shape = sp;
	obj->type = T_SP;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(vec3(0, 1, 0));
	sp->r = get_double_parameter(&line, data) / 2;
	if (sp->r < 0)
		exit_error(ERR_SP ERR_DIAM_POS, data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	parse_cylinder(char *line, t_data *data)
{
	t_obj	*obj;
	t_cy	*cy;

	cy = malloc(sizeof(t_cy));
	obj = malloc(sizeof(t_obj));
	if (obj == NULL || cy == NULL)
		return (free(cy), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->shape = cy;
	obj->type = T_CY;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	cy->r = get_double_parameter(&line, data) / 2;
	cy->h = get_double_parameter(&line, data);
	if (cy->r < 0)
		exit_error(ERR_CY ERR_DIAM_POS, data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	parse_cone(char *line, t_data *data)
{
	t_obj	*obj;
	t_cn	*cn;

	cn = malloc(sizeof(t_cn));
	obj = malloc(sizeof(t_obj));
	if (obj == NULL || cn == NULL)
		return (free(cn), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->shape = cn;
	obj->type = T_CN;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	cn->angle = get_double_parameter(&line, data) * M_PI / 180.0;
	cn->h = get_double_parameter(&line, data);
	if (cn->h < 0)
		exit_error("ERR_CN ERR_HEIGHT_POS", data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	parse_light(char *line, t_data *data)
{
	t_obj	*obj;
	t_light	*light;

	light = malloc(sizeof(t_light));
	obj = malloc(sizeof(t_obj));
	if (obj == NULL || light == NULL)
		return (free(light), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->shape = light;
	obj->type = T_LS;
	obj->pos = get_vec3(&line, data);
	light->ratio = get_double_parameter(&line, data);
	obj->color = get_rgb(&line, data);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		exit_error(ERR_LIGHT ERR_RATIO, data);
	data->scene.light_on = true;
	skip_trailing(line, data);
}
