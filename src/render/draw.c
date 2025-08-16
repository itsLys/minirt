/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/16 14:30:10 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	set_data_cam(t_cam *cam)
{
	double	fov_r;
	t_vec3 world_up = vec3(0, 1, 0);

	double dot = vec3_dot(world_up, cam->norm);
	if (dot < 0)
		dot = -dot;
	if (dot > 0.999)
		world_up = vec3(0, 0, 1);
	cam->right = vec3_norm(vec3_cross(world_up, cam->norm));
	cam->up = vec3_cross(cam->norm, cam->right);
	fov_r = cam->fov * M_PI / 180.0;
	cam->viewport_h = 2.0f * tanf(fov_r / 2.0);
	cam->viewport_w = cam->viewport_h * ((float)WIDTH / (float)HEIGHT);
}

t_ray	get_ray(int x, int y, t_cam *cam)
{
	double	u;
	double	v;
	double	px;
	double	py;
	t_ray	ray;

	u = (x + 0.5) / WIDTH;
	v = (y + 0.5) / HEIGHT;
	px = (u - 0.5) * cam->viewport_w;
	py = (0.5 - v) * cam->viewport_h;	
	ray.orign = cam->pos;
	t_vec3	x_right, y_up;
	x_right = vec3_scale(cam->right, px);
	y_up = vec3_scale(cam->up, py);
	ray.orign = cam->pos;
	ray.dir = vec3_norm(vec3_add(vec3_add(x_right, y_up), cam->norm));
	return (ray);
}

void draw_image(t_data *data)
{
	int x;
	int y;
	int	color;
	// t_vec3 ray;

	x = 0;
	set_data_cam(&(data->scene.cam));
	color = 0x0000FFAA;
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
