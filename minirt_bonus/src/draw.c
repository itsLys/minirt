/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/15 14:52:50 by yel-guad         ###   ########.fr       */
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
	i = 0;
	while (i < WIDTH)
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
