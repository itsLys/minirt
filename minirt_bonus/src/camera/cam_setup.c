/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:18:44 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:37:25 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_viewport(t_cam *cam)
{
	double	fov_r;

	fov_r = cam->fov * M_PI / 180.0;
	cam->viewport_h = 2.0f * tanf(fov_r / 2.0f);
	cam->viewport_w = cam->viewport_h * ((float)WIDTH / (float)HEIGHT);
}

void	setup_cam_coords(t_cam *cam)
{
	t_local_coords *coords;

	coords = &(cam->coords);
	coords->right = vec3_norm(vec3_cross(coords->forward, vec3(0, 1, 0)));
	coords->up = vec3_cross(coords->right, coords->forward);
}
