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

static inline void	img_put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;
	t_img	*img;

	img = &(data->img);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

inline static void	color_pixels(t_data *data, int x, int y, t_rgb color)
{
	int i;
	int j;

	i = 0;
	while (i < data->scale)
	{
		j = 0;
		while (j < data->scale)
		{
			img_put_pixel(data, x + i, y + j, rgb_to_int(color));
			j++;
		}
		i++;
	}
}

void draw_image(t_data *data)
{
	int		i;
	int		j;
	// t_cam_rays	rays;
	t_ray	ray;
	t_rgb	color;

	// rays = data->scene.rays;
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			// if (data->scale == 1)
			// {
			// 	ray.dir = rays.dirs[i][j];
			// 	ray.orign = rays.orig;
			// }
			// else
			ray = map_pixel(i, j, data);
			color = trace_ray(ray, data);
			color_pixels(data, i, j, color);
			j += data->scale;
		}
		i += data->scale;
	}
}
//
