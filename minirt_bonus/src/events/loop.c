/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/10 15:57:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render_img(t_data *data)
{
	// draw_image(data);
	init_threads(data->render_workers);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	join_threads(data->render_workers);
	return (0);
}
