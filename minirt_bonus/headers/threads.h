/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:38:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:39:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "types.h"

void	init_threads(t_worker *worker, int n);
void	join_threads(t_worker *worker, int n);
void	spawn_mapping_workers(t_data *data);
void	set_worker_bounds(t_worker *worker);
void	work_rendering(t_worker *worker);
void	work_directions(t_worker *worker);
void	init_workers(t_worker *worker, t_data *data, void (*func)(t_worker *));

#endif // !THREADS_H
