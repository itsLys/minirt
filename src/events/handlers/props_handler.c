/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:07:22 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/30 16:39:41 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	handle_cam_props(int code, t_cam *cam)
{
	if (code == XK_equal)
		cam->fov = fmin(cam->fov + FOV_STEP, FOV_MAX);
	else if (code == XK_minus)
		cam->fov = fmax(cam->fov - FOV_STEP, 0.0);
	setup_viewport(cam);
}

static inline void	handle_light_props(int code, t_light *light)
{
	if (code == XK_equal)
		light->ratio = fmin(light->ratio + RATIO_STEP, RATIO_MAX);
	else if (code == XK_minus)
		light->ratio = fmax(light->ratio - RATIO_STEP, RATIO_MIN);
}


static inline void	handle_cy_props(int code, t_cy *cy)
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

static inline void	handle_sp_props(int code, t_sp *sp)
{
	if (code == XK_equal)
		sp->r = sp->r + DIAMETER_STEP;
	else if (code == XK_minus)
		sp->r = fmax(sp->r - DIAMETER_STEP, 0.0);
}

void	handle_props(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		handle_cam_props(code, &(data->scene.cam));
	else if (data->selected.type == T_LIGHT)
		handle_light_props(code, &(data->scene.light));
	else if (data->selected.type == T_OBJ && data->selected.obj->type == T_CY)
		handle_cy_props(code, (t_cy *)(data->selected.obj->shape));
	else if (data->selected.type == T_OBJ && data->selected.obj->type == T_SP)
		handle_sp_props(code, (t_sp *)(data->selected.obj->shape));
}
