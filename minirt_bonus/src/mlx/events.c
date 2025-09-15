/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:56:03 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:35:00 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_motion(int code, int x, int y, t_data *data)
{
	(void)code;
	print_ray(x, y, map_pixel(x, y, data));
	return (0);
}

void	setup_mlx(t_data *data)
{
	init_mlx(data);
	init_texture(data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, &clean_exit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &handle_button, data);
	mlx_loop_hook(data->mlx, &render_img, data);
	mlx_loop(data->mlx);
}
