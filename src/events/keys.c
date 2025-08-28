/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/27 15:09:45 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// I need to know which object is selected,
// and the default is camera
#define MOVE_STEP 0.05

void	move_cam(int code, t_data *data)
{
	if (code == XK_Up)
		data->scene.cam.pos.z -= MOVE_STEP;
	else if (code == XK_Down)
		data->scene.cam.pos.z += MOVE_STEP;
	else if (code == XK_Right)
		data->scene.cam.pos.x += MOVE_STEP;
	else if (code == XK_Left)
		data->scene.cam.pos.x -= MOVE_STEP;
	else if (code == XK_Page_Up)
		data->scene.cam.pos.y += MOVE_STEP;
	else if (code == XK_Page_Down)
		data->scene.cam.pos.y -= MOVE_STEP;
}

void	move_light(int code, t_data *data)
{
	if (code == XK_Up)
		data->scene.light.pos.z += MOVE_STEP;
	else if (code == XK_Down)
		data->scene.light.pos.z -= MOVE_STEP;
	else if (code == XK_Right)
		data->scene.light.pos.x += MOVE_STEP;
	else if (code == XK_Left)
		data->scene.light.pos.x -= MOVE_STEP;
	else if (code == XK_Page_Up)
		data->scene.light.pos.y += MOVE_STEP;
	else if (code == XK_Page_Down)
		data->scene.light.pos.y -= MOVE_STEP;
}

void	move_object(int code, t_data *data)
{
	if (code == XK_Up)
		data->selected.obj->pos.z += MOVE_STEP;
	else if (code == XK_Down)
		data->selected.obj->pos.z -= MOVE_STEP;
	else if (code == XK_Right)
		data->selected.obj->pos.x += MOVE_STEP;
	else if (code == XK_Left)
		data->selected.obj->pos.x -= MOVE_STEP;
	else if (code == XK_Page_Up)
		data->selected.obj->pos.y += MOVE_STEP;
	else if (code == XK_Page_Down)
		data->selected.obj->pos.y -= MOVE_STEP;
}

void	handle_obj_move(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		move_cam(code, data);
	else if (data->selected.type == T_LIGHT)
		move_light(code, data);
	else if (data->selected.type == T_OBJ)
		move_object(code, data);
}

// WARN: RGB FOR LIGHT IS NOT IN MANDATORY

#define CAM_FOV_STEP 1.0
void	handle_cam_props(int code, t_data *data)
{
	if (code == XK_equal)
		data->scene.cam.fov = fmin(data->scene.cam.fov + CAM_FOV_STEP, 180.0);
	else if (code == XK_minus)
		data->scene.cam.fov = fmax(data->scene.cam.fov - CAM_FOV_STEP, 0.0);
	setup_cam(&data->scene.cam);
}

void	handle_props(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		handle_cam_props(code, data);
	// else if (data->selected.type == T_LIGHT)
	// 	handle_light_props(code, data);
	// else if (data->selected.type == T_OBJ)
	// 	handle_obj_props(code, data);
}

int	handle_keypress(int code, t_data *data)
{
	if (code == XK_Up || code == XK_Down || code == XK_Left || code == XK_Right
			|| code == XK_Page_Up || code == XK_Page_Down)
		handle_obj_move(code, data);
	else if (code == XK_c)
		data->selected.type = T_CAM;
	else if (code == XK_l)
		data->selected.type = T_LIGHT;
	else if (code == XK_equal || code == XK_minus
			|| code == XK_h || code == XK_s)
		handle_props(code, data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	return 0;
}
