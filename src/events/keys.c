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

void	move_coords(int code, t_vec3 *point)
{
	if (code == XK_Up)
		point->z += MOVE_STEP;
	else if (code == XK_Down)
		point->z -= MOVE_STEP;
	else if (code == XK_Right)
		point->x += MOVE_STEP;
	else if (code == XK_Left)
		point->x -= MOVE_STEP;
	else if (code == XK_Page_Up)
		point->y += MOVE_STEP;
	else if (code == XK_Page_Down)
		point->y -= MOVE_STEP;
}

void	handle_obj_move(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		move_coords(code, &(data->scene.cam.pos));
	else if (data->selected.type == T_LIGHT)
		move_coords(code, &(data->scene.light.pos));
	else if (data->selected.type == T_OBJ)
		move_coords(code, &(data->selected.obj->pos));
}
static void select_object(int code, t_data *data)
{
	if (code == XK_c)
		data->selected.type = T_CAM;
	else if (code == XK_l)
		data->selected.type = T_LIGHT;
}

// WARN: RGB FOR LIGHT IS NOT IN MANDATORY

#define FOV_MAX 180.0
#define FOV_MIN 0.0
#define RATIO_MAX 100.0
#define RATIO_MIN 0.0
#define STEP 1.0
void	handle_cam_props(int code, t_cam *cam)
{
	if (code == XK_equal)
		cam->fov = fmin(cam->fov + STEP, FOV_MAX);
	else if (code == XK_minus)
		cam->fov = fmax(cam->fov - STEP, 0.0);
	setup_cam(cam);
}

void	handle_light_props(int code, t_light *light)
{
	if (code == XK_equal)
		light->ratio = fmin(light->ratio + STEP, RATIO_MAX);
	else if (code == XK_minus)
		light->ratio = fmax(light->ratio - STEP, RATIO_MIN);
}

void	handle_cy_props(int code, t_cy *cy)
{
	if (code == XK_equal)
		cy->d = cy->d + 1;
	else if (code == XK_minus)
		cy->d = fmax(cy->d - STEP, 0.0);
	else if (code == XK_m)
		cy->h = cy->h + 1;
	else if (code == XK_n)
		cy->h = fmax(cy->h - STEP, 0.0);
}

void	handle_sp_props(int code, t_sp *sp)
{
	if (code == XK_equal)
		sp->d = sp->d + 1;
	else if (code == XK_minus)
		sp->d = fmax(sp->d - STEP, 0.0);
}

void	handle_obj_props(int code, t_obj *obj)
{
	if (obj->type == T_CY)
		handle_cy_props(code, (t_cy *)(obj->shape));
	else if (obj->type == T_SP)
		handle_sp_props(code, (t_sp *)(obj->shape));
}

void	handle_props(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		handle_cam_props(code, &(data->scene.cam));
	else if (data->selected.type == T_LIGHT)
		handle_light_props(code, &(data->scene.light));
	else if (data->selected.type == T_OBJ)
		handle_obj_props(code, data->selected.obj);
}

int	handle_keypress(int code, t_data *data)
{
	if (code == XK_Up || code == XK_Down || code == XK_Left || code == XK_Right
			|| code == XK_Page_Up || code == XK_Page_Down)
		handle_obj_move(code, data);
	else if (code == XK_c || code == XK_l)
		select_object(code, data);
	// sp: diameter
	// cy: diamedet height
	// light: ratio
	// camera:	fov
	else if (code == XK_equal || code == XK_minus
			|| code == XK_n || code == XK_m)
		handle_props(code, data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	return 0;
}
