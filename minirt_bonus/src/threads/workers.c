/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:42:59 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/15 15:09:42 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_worker_bounds(t_worker *worker)
{
	int	d;

	d = HEIGHT / SPLIT;
	worker->start.y = worker->number * d;
	if (worker->number == SPLIT - 1)
		worker->end.y = HEIGHT - 1;
	else
		worker->end.y = (worker->number + 1) * d;
	worker->start.x = 0;
	worker->end.x = WIDTH;
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
	static int	thread_number;

	thread_number = SPLIT;
	init_threads(data->mapping_workers, thread_number);
	join_threads(data->mapping_workers, thread_number);
}
