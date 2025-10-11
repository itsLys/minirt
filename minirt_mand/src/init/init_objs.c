/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:58:29 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:32:10 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	obj->color = get_rgb(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
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
	sp->d = get_double_parameter(&line, data);
	if (sp->d < 0)
		exit_error(ERR_SP ERR_DIAM_POS, data);
	sp->r = sp->d / 2.0;
	obj->color = get_rgb(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
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
	cy->d = get_double_parameter(&line, data);
	if (cy->d < 0)
		exit_error(ERR_CY ERR_DIAM_POS, data);
	cy->r = cy->d / 2.0;
	cy->h = get_double_parameter(&line, data);
	obj->color = get_rgb(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
}
