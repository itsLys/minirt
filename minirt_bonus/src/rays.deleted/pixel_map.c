/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:48:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:11:49 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// FIX: functiopn hanging alone ina  loan file
// t_ray	map_pixel(int x, int y, t_data *data)
// {
// 	t_ray	ray;
// 	t_cam	cam;
//
// 	cam = data->scene.cam;
// 	ray.orig = cam.pos;
// 	ray.dir = vec3_add(vec3_scale(data->offsets[y * WIDTH + x].x, cam.coords.right),
// 			vec3_scale(data->offsets[y * WIDTH + x].y, cam.coords.up));
// 	ray.dir = vec3_norm(vec3_add(cam.coords.forward, ray.dir));
// 	return (ray);
// }
