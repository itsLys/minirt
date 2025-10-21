/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:47:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/20 16:04:29 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_next_light(t_data *data)
{
	t_obj	*obj;

	obj = *(data->scene.obj_lst);
	if (data->scene.selected.light == NULL)
		data->scene.selected.light = obj;
	else if (data->scene.selected.light && data->scene.selected.light->next)
	{
		if (data->scene.selected.light->next->type == T_LS)
			data->scene.selected.light = data->scene.selected.light->next;
		else
			data->scene.selected.light = obj;
	}
}

void	select_object(int x, int y, t_data *data)
{
	t_ray	ray;
	t_hit	hit;
	t_obj	*obj;

	ray = map_pixel(x, y, data->scene.cam, data);
	hit.t = INFINITY;
	hit.hit = false;
	hit.obj = NULL;
	obj = *(data->scene.obj_lst);
	record_hit(&obj, &hit, ray);
	if (hit.obj)
	{
		data->scene.selected.obj = hit.obj;
		data->scene.selected.type = T_OBJ;
	}
	else
		data->scene.selected.type = T_CAM;
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
