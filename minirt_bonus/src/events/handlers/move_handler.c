/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:06:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:17:52 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_translate(int code, t_vec3 *point, t_cam cam)
{
	if (code == XK_Up)
		*point = translate(*point, vec3_scale(MOVE_STEP, cam.coords.forward));
	else if (code == XK_Down)
		*point = translate(*point, vec3_scale(-MOVE_STEP, cam.coords.forward));
	else if (code == XK_Right)
		*point = translate(*point, vec3_scale(MOVE_STEP, cam.coords.right));
	else if (code == XK_Left)
		*point = translate(*point, vec3_scale(-MOVE_STEP, cam.coords.right));
	else if (code == XK_Page_Up)
		*point = translate(*point, vec3_scale(MOVE_STEP, cam.coords.up));
	else if (code == XK_Page_Down)
		*point = translate(*point, vec3_scale(-MOVE_STEP, cam.coords.up));
}
//
// void	handle_obj_move(int code, t_data *data)
// {
// 	if (data->scene.selected.type == T_CAM)
// 	{
// 		handle_translate(code, &(data->scene.cam.pos), data->scene.cam);
// 		data->rays.orig = data->scene.cam.pos;
// 	}
// 	else if (data->scene.selected.type == T_LIGHT)
// 		handle_translate(code, &(data->scene.selected.light->pos), data->scene.cam);
// 	else if (data->scene.selected.type == T_OBJ)
// 		handle_translate(code, &(data->scene.selected.obj->pos), data->scene.cam);
// }
