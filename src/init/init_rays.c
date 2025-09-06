/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:11:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:35:57 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_cam_rays(t_cam_rays rays)
{
	int i;

	i = 0;
	while (rays.dirs[i] && i < WIDTH)
		free(rays.dirs[i++]);
	free(rays.dirs);
}

t_cam_rays init_mem(t_data *data)
{
	t_cam_rays rays;
	int			i;

	i = 0;
	rays.dirs = malloc(sizeof(t_vec3 *) * WIDTH);
	if (rays.dirs == NULL)
		clean_exit(data, FAILIURE);
	while (i < WIDTH)
	{
		rays.dirs[i] = malloc(sizeof(t_vec3) * HEIGHT);
		if (rays.dirs[i] == NULL)
			clean_exit(data, FAILIURE);
		i++;
	}
	return rays;
}

void	set_directions(t_cam_rays *rays, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			rays->dirs[i][j] = map_pixel(i, j, data).dir;
			j++;
		}
		i++;
	}
}

void	init_cam_rays(t_data *data)
{
	t_cam_rays rays;

	rays = init_mem(data);
	rays.orig = data->scene.cam.pos;
	set_directions(&rays, data);
	data->scene.rays = rays;
}
