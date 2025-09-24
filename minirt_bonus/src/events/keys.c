/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 10:56:02 by ihajji           ###   ########.fr       */
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

int	handle_keypress(int code, t_data *data)
{
	if (code == XK_Up || code == XK_Down || code == XK_Left || code == XK_Right
			|| code == XK_Page_Up || code == XK_Page_Down)
		handle_obj_move(code, data);
	else if (code == XK_c || code == XK_l)
		handle_obj_select(code, data);
	else if (code == XK_equal || code == XK_minus
			|| code == XK_n || code == XK_m)
		handle_props(code, data);
	else if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	else if (code == XK_d || code == XK_a || code == XK_w || code == XK_s
			|| code == XK_q || code == XK_e)
		handle_rotation(code, data);
	else if (code == XK_p)
		print_scene(data);
	return (0);
}
