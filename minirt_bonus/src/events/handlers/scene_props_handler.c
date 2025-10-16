/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_props_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:45:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/16 10:47:53 by ihajji           ###   ########.fr       */
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
