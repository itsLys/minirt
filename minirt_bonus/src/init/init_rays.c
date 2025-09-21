/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:11:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 11:11:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam_rays	init_mem(t_data *data)
{
	t_cam_rays	rays;

	rays.dirs = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);
	if (rays.dirs == NULL)
		clean_exit(data, FAILIURE);
	return (rays);
}

void	set_directions(t_data *data, t_int_vec2 start, t_int_vec2 end)
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

void	init_cam_rays(t_data *data)
{
	t_cam_rays	rays;
	t_int_vec2	start = {0, 0};
	t_int_vec2	end = {WIDTH, HEIGHT};

	rays = init_mem(data);
	rays.orig = data->scene.cam.pos;
	data->rays = rays;
	set_directions(data, start, end);
}
