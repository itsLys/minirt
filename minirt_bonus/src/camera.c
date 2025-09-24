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
	int	i;
	int	j;

	i = start.x;
	while (i < end.x)
	{
		j = start.y;
		while (j < end.y)
		{
			data->rays.dirs[j * WIDTH + i] = map_pixel(i, j, data).dir;
			j++;
		}
		i++;
	}
}

void	set_offsets(t_vec2 **offsets, t_cam cam) // FIX: make it take cam instead of data
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
	t_local_coords *coords;

	coords = &(cam->coords);
	coords->right = vec3_norm(vec3_cross(coords->forward, vec3(0, 1, 0)));
	coords->up = vec3_cross(coords->right, coords->forward);
}

t_ray	map_pixel(int x, int y, t_data *data)
{
	t_ray	ray;
	t_cam	cam;

	cam = data->scene.cam;
	ray.orig = cam.pos;
	ray.dir = vec3_add(vec3_scale(data->offsets[y * WIDTH + x].x, cam.coords.right),
			vec3_scale(data->offsets[y * WIDTH + x].y, cam.coords.up));
	ray.dir = vec3_norm(vec3_add(cam.coords.forward, ray.dir));
	return (ray);
}
