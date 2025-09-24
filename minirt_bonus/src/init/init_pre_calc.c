/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pre_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:11:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:19:32 by ihajji           ###   ########.fr       */
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


void	init_offsets(t_vec2 **offsets, t_data *data)
{
	*offsets = malloc(sizeof(t_vec2) * WIDTH * HEIGHT);
	if (*offsets == NULL)
		clean_exit(data, FAILIURE);
	set_offsets(offsets, data->scene.cam);
}
