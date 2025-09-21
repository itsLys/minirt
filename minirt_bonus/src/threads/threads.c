/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:24:00 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 11:04:51 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*routine(void *arg)
{
	t_worker *worker;
	worker = (t_worker *) arg;
	worker->function(worker);
	return NULL;
}

void	init_threads(t_worker *worker, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&(worker[i].tid), NULL, routine, worker + i))
			exit_error(NULL, worker->data);
		i++;
	}
}

void	join_threads(t_worker *worker, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(worker[i].tid, NULL);
		i++;
	}
}
