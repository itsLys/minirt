/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 16:34:23 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_image(t_data *data)
{
	int		i;
	int		j;
	t_cam_rays	rays;
	t_ray	ray;
	t_rgb	color;

	rays = data->scene.rays;
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			// ray = map_pixel(i, j, data->scene.cam);
			ray.dir = rays.dirs[i][j];
			ray.orign = rays.orig;
			color = trace_ray(ray, data);
			img_put_pixel(data, i, j, rgb_to_int(color));
			j++;
		}
		i++;
	}
}
//
