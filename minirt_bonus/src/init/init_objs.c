/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:10:06 by yel-guad         ###   ########.fr       */
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
		exit_error(ERR_CY ERR_WRONG_REF, data);
	if (obj->shine < 0 || obj->shine > 200)
		exit_error(ERR_CY ERR_WRONG_SHINE, data);
	skip_trailing(line, data);
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
	obj_lst_add(obj, data->scene.obj_list);
	obj->pos = get_vec3(&line, data);
	pl->norm = get_vec3(&line, data);
	if (vec3_len(pl->norm) != 1)
		exit_error(ERR_PL ERR_NORM_VAL, data);
	// obj->color = get_rgb(&line, data);
	// obj->reflect = get_double(&line, data);
	// obj->shine = get_integer(&line, data);
	// if (obj->reflect < 0.0 || obj->reflect > 1.0)
	// 	exit_error(ERR_PL ERR_WRONG_REF, data);
	// if (obj->shine < 0 || obj->shine > 200)
	// 	exit_error(ERR_PL ERR_WRONG_SHINE, data);
	get_surface_props(obj, line, data);
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
	obj_lst_add(obj, data->scene.obj_list);
	obj->pos = get_vec3(&line, data);
	sp->d = get_double(&line, data);
	if (sp->d < 0)
		exit_error(ERR_SP ERR_DIAM_POS, data);
	sp->r = sp->d / 2.0;
	get_surface_props(obj, line, data);
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
	obj_lst_add(obj, data->scene.obj_list);
	obj->pos = get_vec3(&line, data);
	cy->norm = get_vec3(&line, data);
	if (!is_close(vec3_len(cy->norm), 1.0))
		exit_error(ERR_CY ERR_NORM_VAL, data);
	cy->d = get_double(&line, data);
	if (cy->d < 0)
		exit_error(ERR_CY ERR_DIAM_POS, data);
	cy->r = cy->d / 2.0;
	cy->h = get_double(&line, data);
	get_surface_props(obj, line, data);
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
    obj_lst_add(obj, data->scene.obj_list);
    obj->pos = get_vec3(&line, data);
    cn->norm = get_vec3(&line, data);
    if (!is_close(vec3_len(cn->norm), 1.0))
        exit_error("ERR_CN ERR_NORM_VAL", data);
    cn->angle = get_double(&line, data)* M_PI / 180.0;
    cn->h = get_double(&line, data);
    if (cn->h < 0)
		exit_error("ERR_CN ERR_HEIGHT_POS", data);
	get_surface_props(obj, line, data);
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
    obj_lst_add(obj, data->scene.obj_list);
    obj->pos = get_vec3(&line, data);
	light->ratio = get_double(&line, data);
	obj->color = get_rgb(&line, data);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		exit_error(ERR_LIGHT ERR_RATIO, data);
	data->scene.light_on = true;
	skip_trailing(line, data);
}
