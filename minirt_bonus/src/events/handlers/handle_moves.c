/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 10:04:55 by yel-guad          #+#    #+#             */
/*   Updated: 2025/10/19 11:14:18 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	handle_obj_select(int code, t_data *data)
{
	if (code == XK_c)
		data->scene.selected.type = T_CAM;
	else if (code == XK_l)
	{
		data->scene.selected.type = T_LIGHT;
		select_next_light(data);
	}
}

void	handle_strength(int code, t_data *data)
{
	if (data->scene.selected.type == T_OBJ)
	{
		if (code == XK_z)
			data->scene.selected.obj->tx->strength -= 1;
		else if (code == XK_x)
			data->scene.selected.obj->tx->strength += 1;
	}
}

void	handle_tiling(int code, t_data *data)
{
	t_int_vec2	*tiles;

	if (data->scene.selected.type == T_OBJ)
	{
		tiles = &(data->scene.selected.obj->tiles);
		if (code == XK_g)
			tiles->x = tiles->x + 1;
		else if (code == XK_h)
			tiles->x = fmax(1, tiles->x - 1);
		if (code == XK_t)
			tiles->y = tiles->y + 1;
		else if (code == XK_y)
			tiles->y = fmax(1, tiles->y - 1);
	}
}
