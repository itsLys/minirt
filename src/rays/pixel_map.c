/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:48:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 16:18:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray map_pixel(int x, int y, t_cam cam) // NOTE: vector cam direction instead of lower left
{
	double	px;
	double	py;
	t_ray	ray;

	px = (x + 0.5) / WIDTH;
	py = (y + 0.5) / HEIGHT;
	px = (px - 0.5) * cam.viewport_w;
	py = (0.5 - py) * cam.viewport_h;
	ray.orign = cam.pos;
	ray.dir = vec3_add(vec3_scale(px, cam.right), vec3_scale(py, cam.up));
	ray.dir = vec3_norm(vec3_add(cam.forward, ray.dir));
	return (ray);
}

// camera rays, have the same origin, different direction
// could be:
// t_cam_rays:
// 	t_vec3 dir[WIDTH][HEIGHT];
// 	t_vec3 origin;
//
