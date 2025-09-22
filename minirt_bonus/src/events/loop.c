/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:01:01 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render_img(t_data *data)
{
	static int	threads_number = SPLIT * SPLIT;

	init_threads(data->render_workers, threads_number);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	join_threads(data->render_workers, threads_number);
	return (0);
}
