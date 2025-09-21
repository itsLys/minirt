/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:11:18 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 11:06:35 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_data *data)
{
	data->scene.tx_lst = malloc(sizeof(t_texture *));
	data->scene.patt_lst = malloc(sizeof(t_pattern *));
	data->scene.obj_lst = malloc(sizeof(t_obj *));
	if (data->scene.obj_lst == NULL
			|| data->scene.tx_lst == NULL
			|| data->scene.patt_lst == NULL)
		return (free(data->scene.obj_lst),
				free(data->scene.tx_lst),
				free(data->scene.patt_lst),
				exit_error(NULL, data));
	data->scene.light_on = false;
	data->scene.amb.on = false;
	data->scene.cam.on = false;
	data->scene.selected.type = T_CAM;
	data->scene.selected.light = NULL;
	*(data->scene.obj_lst) = NULL;
	*(data->scene.tx_lst) = NULL;
	*(data->scene.patt_lst) = NULL;
}

void	init_mlx(t_data *data)
{
	data->mlx = NULL;
	data->img.img = NULL;
	data->win = NULL;
}

void	init_workers(t_worker *worker, t_data *data, void (*func)(t_worker *))
{
	int i;

	i = 0;
	while (i < SPLIT * SPLIT)
	{
		worker[i].number = i;
		worker[i].data = data;
		worker[i].function = func;
		set_worker_bounds(worker + i);
		i++;
	}
}

void	init_data(t_data *data)
{
	init_scene(data);
	init_mlx(data);
	data->offsets = NULL;
	data->rays.dirs = NULL;
	data->render_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	data->mapping_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	if (data->render_workers == NULL || data->mapping_workers == NULL)
		return (free(data->render_workers), exit_error(NULL, data));
	init_workers(data->mapping_workers, data, work_directions);
	init_workers(data->render_workers, data, work_rendering);
}
