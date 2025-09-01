/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rotate_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:38:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 11:00:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void cam_rotate_x(int code, t_cam *cam)
{
	if (code == XK_s)
		cam->forward = rotate(cam->forward, cam->right, CAM_ROTATE_STEP);
	else if (code == XK_w)
		cam->forward = rotate(cam->forward, cam->right, CAM_ROTATE_STEP * -1);
	cam->up = vec3_cross(cam->right, cam->forward);
}

static void cam_rotate_z(int code, t_cam *cam)
{
	if (code == XK_e)
		cam->up = rotate(cam->up, cam->forward, CAM_ROTATE_STEP);
	else if (code == XK_q)
		cam->up = rotate(cam->up, cam->forward, CAM_ROTATE_STEP * -1);
	cam->right = vec3_norm(vec3_cross(cam->forward, cam->up));
}

static void cam_rotate_y(int code, t_cam *cam)
{
	if (code == XK_a)
		cam->right = rotate(cam->right, cam->up, CAM_ROTATE_STEP);
	else if (code == XK_d)
		cam->right = rotate(cam->right, cam->up, CAM_ROTATE_STEP * -1);
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
