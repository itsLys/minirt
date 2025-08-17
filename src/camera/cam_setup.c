/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:18:44 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/15 16:22:54 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_cam(t_cam *cam)
{
	double	fov_r;

	cam->backward = vec3_negate(cam->forward);
	cam->right = vec3_norm(vec3_cross(cam->forward, vec3(0, 1, 0)));
	cam->up = vec3_cross(cam->right, cam->forward);
	fov_r = cam->fov * M_PI / 180.0;
	cam->viewport_h = 2.0f * tanf(fov_r / 2.0f);
	cam->viewport_w = cam->viewport_h * ((float)3 / (float)3);
}
