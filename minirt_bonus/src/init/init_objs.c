/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:25:29 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_trailing(char *line, t_data *data)
{
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
}

void	get_surface_props(t_obj *obj, char *line, t_data *data)
{
	obj->color = get_rgb(&line, data);
	obj->reflect = get_double(&line, data);
	obj->shine = get_integer(&line, data);
	if (obj->reflect < 0.0 || obj->reflect > 1.0)
		exit_error(ERR_WRONG_REF, data);
	if (obj->shine < 0 || obj->shine > 200)
		exit_error(ERR_WRONG_SHINE, data);
	skip_trailing(line, data);
}

void	init_local_coords(t_obj *obj)
{
	obj->coords.forward = vec3_cross(vec3(1, 0, 0), obj->coords.up);
	obj->coords.right = vec3_cross(obj->coords.forward, obj->coords.up);
	//
	// TODO: verify correct order and dir
}

void	init_plane(char *line, t_data *data)
{
	t_obj	*obj;
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	obj = malloc(sizeof(t_obj));
	if (!obj || !pl)
		return (free(pl), exit_error(NULL, data));
	obj->shape = pl;
	obj->type = T_PL;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = get_vec3(&line, data);
	if (!is_close(vec3_len(obj->coords.up), 1.0))
		exit_error(ERR_PL ERR_NORM_VAL, data);
	obj_lst_add(obj, data->scene.obj_list);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	init_sphere(char *line, t_data *data)
{
	t_obj	*obj;
	t_sp	*sp;

	sp = malloc(sizeof(t_sp));
	obj = malloc(sizeof(t_obj));
	if (!obj || !sp)
		return (free(sp), exit_error(NULL, data));
	obj->shape = sp;
	obj->type = T_SP;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = vec3(0, 1, 0);
	sp->r = get_double(&line, data) / 2;
	if (sp->r < 0)
		exit_error(ERR_SP ERR_DIAM_POS, data);
	obj_lst_add(obj, data->scene.obj_list);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void	init_cylinder(char *line, t_data *data)
{
	t_obj	*obj;
	t_cy	*cy;

	cy = malloc(sizeof(t_cy));
	obj = malloc(sizeof(t_obj));
	if (obj == NULL || cy == NULL)
		return (free(cy), exit_error(NULL, data));
	obj->shape = cy;
	obj->type = T_CY;
	obj->pos = get_vec3(&line, data);
	obj->coords.up = get_vec3(&line, data);
	cy->r = get_double(&line, data) / 2;
	cy->h = get_double(&line, data);
	if (!is_close(vec3_len(obj->coords.up), 1.0))
		exit_error(ERR_CY ERR_NORM_VAL, data);
	if (cy->r < 0)
		exit_error(ERR_CY ERR_DIAM_POS, data);
	obj_lst_add(obj, data->scene.obj_list);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void    init_cone(char *line, t_data *data)
{
    t_obj        *obj;
    t_cn        *cn;

    cn  = malloc(sizeof(t_cn));
    obj = malloc(sizeof(t_obj));
    if (obj == NULL || cn == NULL)
        return free(cn), exit_error(NULL, data);
    obj->shape = cn;
    obj->type = T_CN;
    obj->pos = get_vec3(&line, data);
    obj->coords.up = get_vec3(&line, data);
    cn->angle = get_double(&line, data) * M_PI / 180.0;
    cn->h = get_double(&line, data);
	if (!is_close(vec3_len(obj->coords.up), 1.0))
		exit_error("ERR_CN ERR_NORM_VAL", data);
    if (cn->h < 0)
		exit_error("ERR_CN ERR_HEIGHT_POS", data);
	obj_lst_add(obj, data->scene.obj_list);
	get_surface_props(obj, line, data);
	init_local_coords(obj);
}

void    init_light(char *line, t_data *data)
{
    t_obj	*obj;
    t_light	*light;

    light  = malloc(sizeof(t_light));
    obj = malloc(sizeof(t_obj));
    if (obj == NULL || light == NULL)
        return free(light), exit_error(NULL, data);
    obj->shape = light;
    obj->type = T_LS;
    obj->pos = get_vec3(&line, data);
	light->ratio = get_double(&line, data);
	obj->color = get_rgb(&line, data);
	obj_lst_add(obj, data->scene.obj_list);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		exit_error(ERR_LIGHT ERR_RATIO, data);
	data->scene.light_on = true;
	skip_trailing(line, data);
}
