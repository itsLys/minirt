/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/23 13:34:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	record_hit(t_obj *obj, t_ray ray, t_data *data)
{
	(void) data; // TODO: remove later
	if (obj->type == T_SP)
		return intersect_sp(ray, obj, (t_sp *)(obj->shape));
	if (obj->type == T_PL)
		return intersect_pl(ray, obj, (t_pl *)(obj->shape));
	if (obj->type == T_CY)
		return intersect_cy(ray, obj, (t_cy *)(obj->shape));
	return ((t_hit) {false});
}

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_hit	tmp;
	t_obj	*obj;

	hit.t = INFINITY;
	hit.hit = 0;
	obj = *(data->scene.obj_list);
	while (obj)
	{
		tmp = record_hit(obj, ray, data);
		if (tmp.hit && tmp.t < hit.t)
		{
			hit = tmp;
			hit.color = obj->color;
		}
		obj = obj->next;
	}
	return compute_color(hit, data);
}
