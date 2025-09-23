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
	data->scene.obj_lst = malloc(sizeof(t_obj *));
	if (data->scene.obj_lst == NULL || data->scene.tx_lst == NULL)
		return (free(data->scene.obj_lst),
				free(data->scene.tx_lst),
				exit_error(NULL, data));
	data->scene.light_on = false;
	data->scene.amb.on = false;
	data->scene.cam.on = false;
	data->scene.selected.type = T_CAM;
	data->scene.selected.light = NULL;
	data->scene.amb.tx = NULL;
	data->scene.amb.tx_name = NULL;
	*(data->scene.obj_lst) = NULL;
	*(data->scene.tx_lst) = NULL;
}
// FIX: normalize direction axis

void	init_workers(t_worker *worker, t_data *data, void (*func)(t_worker *))
{
	int i;

	i = 0;
	while (i < SPLIT * SPLIT)
	{
		worker[i].tid = 0;
		worker[i].number = i;
		worker[i].data = data;
		worker[i].function = func;
		set_worker_bounds(worker + i);
		i++;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit_error(NULL, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, MINIRT_PROJECT);
	if (data->win == NULL)
		exit_error(NULL, data);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img == NULL)
		exit_error(NULL, data);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->img.addr == NULL)
		exit_error(NULL, data);
	setup_mlx(data);
}

void	init_data(t_data *data)
{
	init_scene(data);
	data->mlx = NULL;
	data->img.img = NULL;
	data->win = NULL;
	data->offsets = NULL;
	data->rays.dirs = NULL;
	data->render_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	data->mapping_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	if (data->render_workers == NULL || data->mapping_workers == NULL)
		return (free(data->render_workers), exit_error(NULL, data));
	init_workers(data->mapping_workers, data, work_directions);
	init_workers(data->render_workers, data, work_rendering);
	// FIX: more then 4 threads segv at exit
}
