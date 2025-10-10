/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 15:59:35 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_image(t_data *data, t_int_vec2 start, t_int_vec2 end)
{
	int			i;
	int			j;
	t_cam_rays	rays;
	t_ray		ray;
	t_rgb		color;

	rays = data->rays;
	i = start.x;
	while (i < end.x)
	{
		j = start.y;
		while (j < end.y)
		{
			ray.px.x = i;
			ray.px.y = j;
			ray.dir = rays.dirs[i + j * WIDTH];
			ray.orig = rays.orig;
			color = trace_ray(ray, data);
			img_put_pixel(data->img, i, j, rgb_clamp(color));
			j++;
		}
		i++;
	}
}
