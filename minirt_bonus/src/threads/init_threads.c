/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:24:00 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/10 16:44:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SPLIT 2

void	set_worker_bounds(t_worker *worker)
{
	int	tile_x = worker->number % SPLIT;
	int	tile_y = worker->number / SPLIT;

	int start_x = (WIDTH * tile_x) / SPLIT;
	int start_y = (HEIGHT * tile_y) / SPLIT;

	int end_x = ((WIDTH * (tile_x + 1)) / SPLIT);
	int end_y = ((HEIGHT * (tile_y + 1)) / SPLIT);

	worker->start.x = start_x;
	worker->start.y = start_y;
	worker->end.x = end_x;
	worker->end.y = end_y;
}

void	*routine(void *arg)
{
	// t_data *data;
	t_worker *worker;

	worker = (t_worker *) arg;
	// data = worker->data;
	set_worker_bounds(worker);
	draw_image(worker);
	return NULL;
}

void	init_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < SPLIT * SPLIT)
	{
		if (pthread_create(&(data->workers[i].tid), NULL, routine, data->workers + i))
			exit_error(NULL, data);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < SPLIT * SPLIT)
	{
		pthread_join(data->workers[i].tid, NULL);
		i++;
	}
}

