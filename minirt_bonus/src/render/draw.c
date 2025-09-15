/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/10 16:28:41 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	img_put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;
	t_img	*img;

	img = &(data->img);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_image(t_worker *worker)
{
	int			i;
	int			j;
	t_cam_rays	rays;
	t_ray		ray;
	t_rgb		color;

	rays = worker->data->scene.rays;
	i = worker->start.x;
	while (i < worker->end.x)
	{
		j = worker->start.y;
		while (j < worker->end.y)
		{
			ray.pixel.x = i;
			ray.pixel.y = j;
			ray.dir = rays.dirs[i][j];
			ray.orign = rays.orig;
			// ray = map_pixel(i, j, worker->data);
			color = trace_ray(ray, worker->data);
			img_put_pixel(worker->data, i, j, rgb_to_int(color));
			j++;
		}
		i++;
	}
}
//
