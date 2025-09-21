/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:42:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 11:04:31 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_worker_bounds(t_worker *worker)
{
	// TODO: fham
	t_int_vec2	tile;
	t_int_vec2	start;
	t_int_vec2	end;

	tile.x = worker->number % SPLIT;
	tile.y = worker->number / SPLIT;
	start.x = (WIDTH * tile.x) / SPLIT;
	start.y = (HEIGHT * tile.y) / SPLIT;
	end.x = ((WIDTH * (tile.x + 1)) / SPLIT);
	end.y = ((HEIGHT * (tile.y + 1)) / SPLIT);
	worker->start.x = start.x;
	worker->start.y = start.y;
	worker->end.x = end.x;
	worker->end.y = end.y;
}

void	work_rendering(t_worker *worker)
{
	t_data		*data;
	t_int_vec2	start;
	t_int_vec2	end;

	data = worker->data;
	start = worker->start;
	end = worker->end;
	draw_image(data, start, end);
}

void	work_directions(t_worker *worker)
{
	t_data		*data;
	t_int_vec2	start;
	t_int_vec2	end;

	data = worker->data;
	start = worker->start;
	end = worker->end;
	set_directions(data, start, end);
}

void	spawn_mapping_workers(t_data *data)
{
	static int	thread_number = SPLIT * SPLIT;

	init_threads(data->mapping_workers, thread_number);
	join_threads(data->mapping_workers, thread_number);
}
