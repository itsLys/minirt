/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:35 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/30 10:17:39 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_object(int x, int y, t_data *data)
{
	t_ray	ray;
	t_hit	hit;
	t_hit	tmp;
	t_obj	*obj;
	t_obj	*hit_obj;

	ray = map_pixel(x, y, data->scene.cam);
	hit.t = INFINITY;
	hit.hit = false;
	obj = *(data->scene.obj_list);
	while (obj)
	{
		tmp = record_hit(obj, ray, data);
		if (tmp.hit && tmp.t < hit.t)
		{
			hit = tmp;
			hit_obj = obj;
		}
		obj = obj->next;
	}
	data->selected.obj = hit_obj;
	data->selected.type = T_OBJ;
}

int	handle_button(int code, int x, int y, t_data *data)
{
	if (code == 1)
		select_object(x, y, data);
	printf("mouse button pressed: %d\n", code);
	return 0;
}
