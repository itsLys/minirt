/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:02:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	select_next_light(t_data *data)
{
	t_obj			*obj;

	obj = *(data->scene.obj_list);
	if (data->selected.light == NULL)
		data->selected.light = obj;
	else if (data->selected.light && data->selected.light->next)
	{
		if (data->selected.light->next->type == T_LS)
			data->selected.light = data->selected.light->next;
		else
			data->selected.light = obj;
	}
	data->selected.type = T_LIGHT;
	printf("selected light:	");
	print_vec3(data->selected.light->pos);
	printf("\n");
}

static void	handle_obj_select(int code, t_data *data)
{
	if (code == XK_c)
		data->selected.type = T_CAM;
	else if (code == XK_l)
		select_next_light(data);
}

static void	handle_rotation(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
	{
		handle_cam_rotate(code, &(data->scene.cam));
		spawn_mapping_workers(data);
	}
	else if (data->selected.type == T_OBJ)
		handle_obj_rotate(code, data->selected.obj, data->scene.cam);
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
