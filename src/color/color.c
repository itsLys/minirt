/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/28 11:17:06 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit	record_shadow(t_obj *obj, t_ray ray)
{
	if (obj->type == T_SP)
		return intersect_sp(ray, obj, (t_sp *)(obj->shape));
	if (obj->type == T_PL)
		return intersect_pl(ray, obj, (t_pl *)(obj->shape));
	if (obj->type == T_CY)
		return intersect_cy(ray, obj, (t_cy *)(obj->shape));
	return (t_hit){0};
}

static bool	is_shadow(t_hit hit, t_data *data)
{
	t_hit	tmp;
	t_obj	*obj;
	t_ray	ray;
	double	light_distance;

	ray.orign = hit.point;
	ray.dir = vec3_subtract(data->scene.light.pos, hit.point);
	light_distance = vec3_len(ray.dir);
	ray.dir = vec3_norm(ray.dir);
	obj = *(data->scene.obj_list);
	while (obj)
	{
		tmp = record_shadow(obj, ray);
		if (tmp.hit && tmp.t > EPS && is_less_then(tmp.t, light_distance))
			return (true);
		obj = obj->next;
	}
	return (false);
}

static t_rgb compute_defuse(t_hit hit, t_data *data)
{
	t_vec3	light_dir;
	t_light	light;
	t_rgb	rgb;
	double	dot;

	light = data->scene.light;
	light_dir = vec3_norm(vec3_subtract(light.pos, hit.point));
	dot = vec3_dot(hit.normal, light_dir);
	if (dot < 0 || is_shadow(hit, data))
		return (t_rgb) {0};
	rgb.r = (fmax(0.0, dot) * light.ratio * light.color.r * hit.color.r);
	rgb.g = (fmax(0.0, dot) * light.ratio * light.color.g * hit.color.g);
	rgb.b = (fmax(0.0, dot) * light.ratio * light.color.b * hit.color.b);
	return rgb;
}

t_rgb	compute_color(t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	defuse;

	if (hit.hit == false)
		return int_to_rgb(BG_COLOR);
	amb = compute_amb(hit.color, data->scene.amb_light);
	defuse = compute_defuse(hit, data);
	return rgb(amb.r + defuse.r,
			amb.g + defuse.g,
			amb.b + defuse.b);
}
