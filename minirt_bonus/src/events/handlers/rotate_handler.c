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

static void	rotate_x(int code, t_local_coords *coords)
{
	if (code == XK_s)
		coords->forward = rotate(coords->forward, coords->right, ROTATE_STEP);
	else if (code == XK_w)
		coords->forward = rotate(coords->forward, coords->right, ROTATE_STEP * -1);
	coords->up = vec3_cross(coords->right, coords->forward);
}

static void	rotate_z(int code, t_local_coords *coords)
{
	if (code == XK_e)
		coords->up = rotate(coords->up, coords->forward, ROTATE_STEP);
	else if (code == XK_q)
		coords->up = rotate(coords->up, coords->forward, ROTATE_STEP * -1);
	coords->right = vec3_norm(vec3_cross(coords->forward, coords->up));
}

static void	rotate_y(int code, t_local_coords *coords)
{
	if (code == XK_a)
		coords->right = rotate(coords->right, coords->up, CAM_ROTATE_STEP);
	else if (code == XK_d)
		coords->right = rotate(coords->right, coords->up, CAM_ROTATE_STEP * -1);
	coords->forward = vec3_cross(coords->up, coords->right);
}

void	handle_coords_rotate(int code, t_local_coords *coords)
{
	if (code == XK_w || code == XK_s)
		rotate_x(code, coords);
	else if (code == XK_a || code == XK_d)
		rotate_y(code, coords);
	else if (code == XK_q || code == XK_e)
		rotate_z(code, coords);
}
