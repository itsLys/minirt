/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:38:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/19 11:09:40 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_tilt(int code, t_local_coords *coords)
{
	if (code == XK_w)
		coords->forward = rotate(coords->forward,
				coords->right, CAM_ROTATE_STEP);
	else if (code == XK_s)
		coords->forward = rotate(coords->forward,
				coords->right, CAM_ROTATE_STEP * -1);
	coords->up = vec3_norm(vec3_cross(coords->right, coords->forward));
}

void	rotate_turn(int code, t_local_coords *coords)
{
	if (code == XK_e)
		coords->up = rotate(coords->up, coords->forward, CAM_ROTATE_STEP);
	else if (code == XK_q)
		coords->up = rotate(coords->up, coords->forward, CAM_ROTATE_STEP * -1);
	coords->right = vec3_norm(vec3_cross(coords->forward, coords->up));
}

void	rotate_spin(int code, t_local_coords *coords)
{
	if (code == XK_a)
		coords->right = rotate(coords->right, coords->up, CAM_ROTATE_STEP);
	else if (code == XK_d)
		coords->right = rotate(coords->right, coords->up, CAM_ROTATE_STEP * -1);
	coords->forward = vec3_norm(vec3_cross(coords->up, coords->right));
}
