/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/20 13:07:04 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_keyrelease(int key, t_data *data)
{
	if (key < 65536)
		data->keys[key] = 0;
	return (0);
}

int	handle_keypress(int code, t_data *data)
{
	if (code < 65536)
		data->keys[code] = 1;
	if (code == XK_c)
		handle_obj_select(XK_c, data);
	else if (code == XK_l)
		handle_obj_select(XK_l, data);
	else if (code == XK_p)
		print_scene(data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, DestroyNotify, NoEventMask, &clean_exit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &handle_button, data);
	mlx_loop_hook(data->mlx, &render_img, data);
}

int	render_img(t_data *data)
{
	handle_held_keys1(data);
	handle_held_keys2(data);
	init_threads(data->render_workers, SPLIT);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	join_threads(data->render_workers, SPLIT);
	return (0);
}
