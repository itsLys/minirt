/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/15 08:56:39 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_keyrelease(int key, t_data *data)
{
	if (key < 65536)
		data->keys[key] = 0;
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

void	handle_rotation(int code, t_data *data)
{
	if (data->scene.selected.type == T_CAM)
	{
		handle_coords_rotate(code, &(data->scene.cam.coords));
		spawn_mapping_workers(data);
	}
	else if (data->scene.selected.type == T_OBJ)
		handle_coords_rotate(code, &(data->scene.selected.obj->coords));
}

int	render_img(t_data *data)
{
	static int	threads_number;

	if (data->keys[XK_Up])
		handle_obj_move(XK_Up, data);
	if (data->keys[XK_Down])
		handle_obj_move(XK_Down, data);
	if (data->keys[XK_Left])
		handle_obj_move(XK_Left, data);
	if (data->keys[XK_Right])
		handle_obj_move(XK_Right, data);

	if (data->keys[XK_w])
		handle_rotation(XK_w, data);
	if (data->keys[XK_s])
		handle_rotation(XK_s, data);
	if (data->keys[XK_a])
		handle_rotation(XK_a, data);
	if (data->keys[XK_d])
		handle_rotation(XK_d, data);

	if (data->keys[XK_Escape])
		clean_exit(data, SUCCESS);
		
	// Already exists
	threads_number = SPLIT * SPLIT;
	init_threads(data->render_workers, threads_number);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	join_threads(data->render_workers, threads_number);
	return (0);
}
