/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:07:22 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:23:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_cam_props(int code, t_cam *cam)
{
	if (code == XK_equal)
		cam->fov = fmin(cam->fov + FOV_STEP, FOV_MAX);
	else if (code == XK_minus)
		cam->fov = fmax(cam->fov - FOV_STEP, 0.0);
	setup_viewport(cam);
}

void	handle_light_props(int code, t_light *light)
{
	if (code == XK_equal)
		light->ratio = fmin(light->ratio + RATIO_STEP, RATIO_MAX);
	else if (code == XK_minus)
		light->ratio = fmax(light->ratio - RATIO_STEP, RATIO_MIN);
}

void	handle_cy_props(int code, t_cy *cy)
{
	if (code == XK_equal)
		cy->r = cy->r + DIAMETER_STEP;
	else if (code == XK_minus)
		cy->r = fmax(cy->r - DIAMETER_STEP, 0.0);
	else if (code == XK_m)
		cy->h = cy->h + DIAMETER_STEP;
	else if (code == XK_n)
		cy->h = fmax(cy->h - DIAMETER_STEP, 0.0);
}

void	handle_cn_props(int code, t_cn *cn)
{
	if (code == XK_equal)
		cn->angle = cn->angle + DIAMETER_STEP;
	else if (code == XK_minus)
		cn->angle = fmax(cn->angle - DIAMETER_STEP, 0.0);
	else if (code == XK_m)
		cn->h = cn->h + DIAMETER_STEP;
	else if (code == XK_n)
		cn->h = fmax(cn->h - DIAMETER_STEP, 0.0);
}

void	handle_sp_props(int code, t_sp *sp)
{
	if (code == XK_equal)
		sp->r = sp->r + DIAMETER_STEP;
	else if (code == XK_minus)
		sp->r = fmax(sp->r - DIAMETER_STEP, 0.0);
}

// void	handle_props(int code, t_data *data)
// {
// 	if (data->scene.selected.type == T_CAM)
// 	{
// 		handle_cam_props(code, &(data->scene.cam));
// 		set_offsets(&(data->offsets), data);
// 		spawn_mapping_workers(data);
// 	}
// 	else if (data->scene.selected.type == T_LIGHT)
// 		handle_light_props(code, (t_light *)(data->scene.selected.light->shape));
// 	else if (data->scene.selected.type == T_OBJ && data->scene.selected.obj->type == T_CY)
// 		handle_cy_props(code, (t_cy *)(data->scene.selected.obj->shape));
// 	else if (data->scene.selected.type == T_OBJ && data->scene.selected.obj->type == T_CN)
// 		handle_cn_props(code, (t_cn *)(data->scene.selected.obj->shape));
// 	else if (data->scene.selected.type == T_OBJ && data->scene.selected.obj->type == T_SP)
// 		handle_sp_props(code, (t_sp *)(data->scene.selected.obj->shape));
// }
