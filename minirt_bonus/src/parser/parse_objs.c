/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 15:01:52 by yel-guad         ###   ########.fr       */
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
	obj->bmp_strenght = STRENGTH;
	obj->shape = pl;
	obj->type = T_PL;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	if (is_close(0, vec3_len(obj->coords.up)))
		exit_error(ERR_PL ERR_ORIENT, data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	parse_sphere(char *line, t_data *data)
{
	t_obj	*obj;
	t_sp	*sp;

	sp = malloc(sizeof(t_sp));
	obj = malloc(sizeof(t_obj));
	if (!obj || !sp)
		return (free(sp), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->bmp_strenght = STRENGTH;
	obj->shape = sp;
	obj->type = T_SP;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(vec3(0, 1, 0));
	sp->r = get_double_parameter(&line, data) / 2;
	if (sp->r < 0)
		exit_error(ERR_SP ERR_DIAM_HEIGHT, data);
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
	obj->bmp_strenght = STRENGTH;
	obj->shape = cy;
	obj->type = T_CY;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	cy->r = get_double_parameter(&line, data) / 2;
	cy->h = get_double_parameter(&line, data);
	if (cy->r < 0 || cy->h < 0)
		exit_error(ERR_CY ERR_DIAM_HEIGHT, data);
	if (is_close(0, vec3_len(obj->coords.up)))
		exit_error(ERR_CY ERR_ORIENT, data);
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
	obj->bmp_strenght = STRENGTH;
	obj->shape = cn;
	obj->type = T_CN;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	cn->angle = get_double_parameter(&line, data);
	if (fabs(fmod(cn->angle, 360.0)) == 180.0)
		exit_error("use a different angle for cone\n", data);
	cn->angle = cn->angle * M_PI / 360;
	cn->h = get_double_parameter(&line, data);
	if (cn->h < 0 || cn->angle < 0)
		exit_error("ERR_CN ERR_DIAM_HEIGHT", data);
	if (is_close(0, vec3_len(obj->coords.up)))
		exit_error(ERR_CN ERR_ORIENT, data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	parse_rectangle(char *line, t_data *data)
{
	t_obj	*obj;
	t_rc	*rc;

	rc = malloc(sizeof(t_rc));
	obj = malloc(sizeof(t_obj));
	if (!obj || !rc)
		return (free(rc), exit_error(NULL, data));
	obj_lst_add(obj, data->scene.obj_lst);
	obj->bmp_strenght = STRENGTH;
	obj->shape = rc;
	obj->type = T_RC;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3_norm(get_vec3(&line, data));
	rc->width = get_double_parameter(&line, data);
	rc->height = get_double_parameter(&line, data);
	if (rc->height <= 0 || rc->width <= 0)
		exit_error("ERR_RC ERR_DIAM_HEIGHT", data);
	if (is_close(0, vec3_len(obj->coords.up)))
		exit_error(ERR_RC ERR_ORIENT, data);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}
