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
	t_obj	*obj;

	ray = map_pixel(x, y, data);
	hit.t = INFINITY;
	hit.hit = false;
	hit.obj = NULL;
	obj = *(data->scene.obj_list);
	record_hit(&obj, &hit, ray);
	if (hit.obj)
	{
		data->selected.obj = hit.obj;
		data->selected.type = T_OBJ;
	}
	else
		data->selected.type = T_CAM;
}

int	handle_button(int code, int x, int y, t_data *data)
{
	if (code == 1)
		select_object(x, y, data);
	printf("mouse button pressed: %d\n", code);
	return 0;
}
