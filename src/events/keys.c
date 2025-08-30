/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/30 17:02:34 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// WARN: RGB FOR LIGHT IS NOT IN MANDATORY

#define ROTATE_STEP 0.01

static void handle_obj_select(int code, t_data *data)
{
	if (code == XK_c)
		data->selected.type = T_CAM;
	else if (code == XK_l)
		data->selected.type = T_LIGHT;
}

/* v_rotate(a) = v cos(a) + (k x v)sin(a) + k(k.v)(1 - cos(a)) */
t_vec3	rotate(t_vec3 to_rot, t_vec3 rot_around, double	angle)
{
	t_vec3	v_cos = vec3_scale(cosf(angle), to_rot);
	t_vec3	cross_sin = vec3_scale(sinf(angle), vec3_cross(rot_around, to_rot));
	t_vec3 kkv = vec3_scale(vec3_dot(rot_around, to_rot), to_rot);
	kkv = vec3_scale(1.0 - cosf(angle), kkv);

	t_vec3 new;

	new = vec3_add(v_cos, cross_sin);
	new = vec3_add(new, kkv);
	return new;

}

void cam_rotate_x(int code, t_cam *cam)
{
	if (code == XK_w)
		cam->forward = rotate(cam->forward, cam->right, ROTATE_STEP);
	else if (code == XK_s)
		cam->forward = rotate(cam->forward, cam->right, ROTATE_STEP * -1);
}

void cam_rotate_z(int code, t_cam *cam)
{
	if (code == XK_e)
		cam->up = rotate(cam->up, cam->forward, ROTATE_STEP);
	else if (code == XK_q)
		cam->up = rotate(cam->up, cam->forward, ROTATE_STEP * -1);
	cam->right = vec3_norm(vec3_cross(cam->forward, cam->up));
}

void cam_rotate_y(int code, t_cam *cam)
{
	if (code == XK_d)
		cam->right = rotate(cam->right, cam->up, ROTATE_STEP);
	else if (code == XK_a)
		cam->right = rotate(cam->right, cam->up, ROTATE_STEP * -1);
	cam->forward = vec3_cross(cam->up, cam->right);
}

void	handle_cam_rotate(int code, t_cam *cam)
{
	if (code == XK_w || code == XK_s)
		cam_rotate_x(code, cam);
	else if (code == XK_a || code == XK_d)
		cam_rotate_y(code, cam);
	else if (code == XK_q || code == XK_e)
		cam_rotate_z(code, cam);
}

void handle_rotation(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		handle_cam_rotate(code, &(data->scene.cam));
}

int	handle_keypress(int code, t_data *data)
{
	if (code == XK_Up || code == XK_Down || code == XK_Left || code == XK_Right
			|| code == XK_Page_Up || code == XK_Page_Down)
		handle_obj_move(code, data);
	else if (code == XK_c || code == XK_l)
		handle_obj_select(code, data);
	else if (code == XK_equal || code == XK_minus
			|| code == XK_n || code == XK_m)
		handle_props(code, data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	else if (code == XK_d || code == XK_a || code == XK_w || code == XK_s || code == XK_q || code == XK_e)
		handle_rotation(code, data);
	return 0;
}
