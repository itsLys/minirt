/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/10 18:26:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_obj_select(int code, t_data *data)
{
	if (code == XK_c)
		data->scene.selected.type = T_CAM;
	else if (code == XK_l)
	{
		data->scene.selected.type = T_LIGHT;
		select_next_light(data);
	}
}

static void	handle_rotation(int code, t_data *data)
{
	if (data->scene.selected.type == T_CAM)
	{
		handle_coords_rotate(code, &(data->scene.cam.coords));
		spawn_mapping_workers(data);
	}
	else if (data->scene.selected.type == T_OBJ)
		handle_coords_rotate(code, &(data->scene.selected.obj->coords));
}

static void	handle_tiling(int code, t_data *data)
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

int	handle_keypress(int code, t_data *data)
{
	if (code == XK_Up || code == XK_Down || code == XK_Left || code == XK_Right
		|| code == XK_Page_Up || code == XK_Page_Down)
		handle_obj_move(code, data);
	else if (code == XK_c || code == XK_l)
		handle_obj_select(code, data);
	else if (code == XK_equal || code == XK_minus || code == XK_n
		|| code == XK_m)
		handle_props(code, data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	else if (code == XK_d || code == XK_a || code == XK_w || code == XK_s
		|| code == XK_q || code == XK_e)
		handle_rotation(code, data);
	else if (code == XK_p)
		print_scene(data);
	else if (code == XK_g || code == XK_h || code == XK_t || code == XK_y)
		handle_tiling(code, data);
	return (0);
}
