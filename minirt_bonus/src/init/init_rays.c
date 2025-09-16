/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:11:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:16:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_cam_rays(t_cam_rays rays)
{
	// int	i;
	//
	// i = 0;
	// while (rays.dirs[i] && i < WIDTH)
	// 	free(rays.dirs[i++]);
	free(rays.dirs);
}

t_cam_rays	init_mem(t_data *data)
{
	t_cam_rays	rays;
	// int			i;

	// i = 0;
	rays.dirs = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);
	if (rays.dirs == NULL)
		clean_exit(data, FAILIURE);

	// while (i < WIDTH)
	// {
	// 	rays.dirs[i] = calloc(sizeof(t_vec3), HEIGHT);
	// 	if (rays.dirs[i] == NULL)
	// 		clean_exit(data, FAILIURE);
	// 	i++;
	// }
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
			data->scene.rays.dirs[j * WIDTH + i] = map_pixel(i, j, data).dir;
			j++;
		}
		i++;
	}
}

void	spawn_mapping_workers(t_data *data)
{
	static int	thread_number = SPLIT * SPLIT;
	init_threads(data->mapping_workers, thread_number);
	join_threads(data->mapping_workers, thread_number);
}


void	init_cam_rays(t_data *data)
{
	t_cam_rays	rays;
	t_int_vec2	start = {0, 0};
	t_int_vec2	end = {WIDTH, HEIGHT};

	rays = init_mem(data);
	rays.orig = data->scene.cam.pos;
	data->scene.rays = rays;
	set_directions(data, start, end);
}
