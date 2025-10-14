/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:39:14 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:42:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit	record_shadow(t_obj *obj, t_ray ray)
{
	if (obj->type == T_SP)
		return (intersect_sp(ray, obj, (t_sp *)(obj->shape)));
	if (obj->type == T_PL)
		return (intersect_pl(ray, obj, (t_pl *)(obj->shape)));
	if (obj->type == T_CY)
		return (intersect_cy(ray, obj, (t_cy *)(obj->shape)));
	if (obj->type == T_CN)
		return (intersect_cn(ray, obj, (t_cn *)(obj->shape)));
	if (obj->type == T_RC)
		return (intersect_rc(ray, obj, (t_rc *)(obj->shape)));
	return ((t_hit){0});
}

bool	is_shadow(t_hit hit, t_obj *light, t_data *data)
{
	t_hit	tmp;
	t_obj	*obj;
	t_ray	ray;
	double	light_distance;

	ray.orig = hit.point;
	ray.dir = vec3_subtract(light->pos, hit.point);
	light_distance = vec3_len(ray.dir);
	ray.dir = vec3_norm(ray.dir);
	obj = *(data->scene.obj_lst);
	while (obj)
	{
		tmp = record_shadow(obj, ray);
		if (tmp.hit && tmp.t > EPS && is_less_then(tmp.t, light_distance))
			return (true);
		obj = obj->next;
	}
	return (false);
}
