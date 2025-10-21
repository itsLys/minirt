/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:18:44 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:11:15 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_directions(t_data *data, t_int_vec2 start, t_int_vec2 end) // move
{
	int		i;
	int		j;
	t_vec3	ray_dir;

	i = start.x;
	while (i < end.x)
	{
		j = start.y;
		while (j < end.y)
		{
			ray_dir = map_pixel(i, j, data->scene.cam, data).dir;
			data->rays.dirs[j * WIDTH + i] = ray_dir;
			j++;
		}
		i++;
	}
}

void	set_offsets(t_vec2 **offsets, t_cam cam)
{
	int		i;
	int		j;
	double	px;
	double	py;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			px = (i + 0.5) / WIDTH;
			py = (j + 0.5) / HEIGHT;
			px = (px - 0.5) * cam.viewport_w;
			py = (0.5 - py) * cam.viewport_h;
			(*offsets)[j * WIDTH + i].x = px;
			(*offsets)[j * WIDTH + i].y = py;
			j++;
		}
		i++;
	}
}

void	setup_viewport(t_cam *cam)
{
	double	fov_r;

	fov_r = cam->fov * M_PI / 180.0;
	cam->viewport_h = 2.0f * tanf(fov_r / 2.0f);
	cam->viewport_w = cam->viewport_h * ((float)WIDTH / (float)HEIGHT);
}

void	setup_cam_coords(t_cam *cam)
{
	t_local_coords	*coords;
	t_vec3			tmp;

	tmp = vec3(0, 1, 0);
	if (is_close(fabs(vec3_dot(tmp, cam->coords.forward)), 1))
		tmp = vec3(1, 0, 0);
	coords = &(cam->coords);
	coords->right = vec3_norm(vec3_cross(coords->forward, tmp));
	coords->up = vec3_cross(coords->right, coords->forward);
}

t_ray	map_pixel(int x, int y, t_cam cam, t_data *data)
{
	t_ray	ray;
	t_vec2	offsets;
	t_vec3	ray_up;
	t_vec3	ray_right;
	t_vec3	ray_forward;

	cam = data->scene.cam;
	ray.orig = cam.pos;
	offsets.x = data->offsets[y * WIDTH + x].x;
	offsets.y = data->offsets[y * WIDTH + x].y;
	ray_right = vec3_scale(offsets.x, cam.coords.right);
	ray_up = vec3_scale(offsets.y, cam.coords.up);
	ray_forward = vec3_add(ray_right, ray_up);
	ray_forward = vec3_add(cam.coords.forward, ray_forward);
	ray.dir = vec3_norm(ray_forward);
	return (ray);
}
