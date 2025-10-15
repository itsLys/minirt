/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:51:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 13:19:42 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_props(int code, t_data *data)
{
	if (data->scene.selected.type == T_CAM)
	{
		handle_cam_props(code, &(data->scene.cam));
		set_offsets(&(data->offsets), data->scene.cam);
		spawn_mapping_workers(data);
	}
	else if (data->scene.selected.type == T_LIGHT)
		handle_light_props(code,
			(t_light *)(data->scene.selected.light->shape));
	else if (data->scene.selected.type == T_OBJ
		&& data->scene.selected.obj->type == T_CY)
		handle_cy_props(code, (t_cy *)(data->scene.selected.obj->shape));
	else if (data->scene.selected.type == T_OBJ
		&& data->scene.selected.obj->type == T_CN)
		handle_cn_props(code, (t_cn *)(data->scene.selected.obj->shape));
	else if (data->scene.selected.type == T_OBJ
		&& data->scene.selected.obj->type == T_SP)
		handle_sp_props(code, (t_sp *)(data->scene.selected.obj->shape));
	else if (data->scene.selected.type == T_OBJ
		&& data->scene.selected.obj->type == T_RC)
		handle_rc_props(code, (t_rc *)(data->scene.selected.obj->shape));
}

void	handle_obj_move(int code, t_data *data)
{
	if (data->scene.selected.type == T_CAM)
	{
		handle_translate(code, &(data->scene.cam.pos), data->scene.cam);
		data->rays.orig = data->scene.cam.pos;
	}
	else if (data->scene.selected.type == T_LIGHT)
		handle_translate(code, &(data->scene.selected.light->pos),
			data->scene.cam);
	else if (data->scene.selected.type == T_OBJ)
		handle_translate(code, &(data->scene.selected.obj->pos),
			data->scene.cam);
}

void	handle_coords_rotate(int code, t_local_coords *coords)
{
	if (code == XK_w || code == XK_s)
		rotate_tilt(code, coords);
	else if (code == XK_a || code == XK_d)
		rotate_spin(code, coords);
	else if (code == XK_q || code == XK_e)
		rotate_turn(code, coords);
}

int	handle_button(int code, int x, int y, t_data *data)
{
	if (code == 1)
		select_object(x, y, data);
	return (0);
}
