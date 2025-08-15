/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/15 11:47:11 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	map_pixel(int x, int y, t_data *data)
{
	
}

void	set_data_cam(t_cam *cam)
{
	t_vec3	right;
	double	fov_r;

	right = vec3_norm(vec3_cross(vec3(0, 1, 0), cam->norm));
	cam->up = vec3_cross(cam->norm, right);
	fov_r = cam->fov * M_PI / 180.0;
	cam->viewport_h = 2.0f * tanf(fov_r / 2.0f);
	cam->viewport_w = cam->viewport_h * ((float)WIDTH / (float)HEIGHT);
}

void draw_image(t_data *data)
{
	int x;
	int y;
	int	color;
	// t_vec3 ray;

	x = 0;
	color = 0x0000FF00;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// ray = map_pixel(x, y, data);
			// color = compute_color(ray, data);
			// map_each_pixel
			// compute_color
			img_put_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}
//
