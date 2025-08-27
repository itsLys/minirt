/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:48:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/27 11:50:43 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray map_pixel(int x, int y, t_cam cam) // NOTE: vector cam direction instead of lower left
{
	double	x_prop;
	double	y_prop;
	// t_vec3	lower_left;
	// t_vec3	pixel_pos;
	t_ray	ray;

	x_prop = (x + 0.5) / WIDTH - 0.5;
	y_prop = (0.5 - y) / HEIGHT - 0.5;
	ray.orign = cam.pos;
	ray.dir = vec3_add(vec3_scale(x_prop * (cam.viewport_w / 2), cam.right), vec3_scale(y_prop * (cam.viewport_h/2), cam.up));
	ray.dir = vec3_add(cam.forward, ray.dir);
	ray.dir = vec3_norm(vec3_subtract(ray.dir, cam.pos));
	// lower_left = vec3_add(cam.pos, cam.forward);
	// lower_left = vec3_subtract(lower_left, vec3_scale(cam.viewport_w/2.0, cam.right));
	// lower_left = vec3_subtract(lower_left, vec3_scale(cam.viewport_h/2.0, cam.up));
	// pixel_pos = vec3_add(lower_left, vec3_scale(x_prop * cam.viewport_w, cam.right));
	// pixel_pos = vec3_add(pixel_pos, vec3_scale(y_prop * cam.viewport_h, cam.up));
	// ray.dir = vec3_norm(vec3_subtract(pixel_pos, cam.pos));
	return (ray);
}
