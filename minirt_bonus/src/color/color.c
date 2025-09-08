/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:17:29 by yel-guad         ###   ########.fr       */
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
	return ((t_hit){0});
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

static inline t_rgb	compute_amb(t_rgb obj, t_light amb)
{
	t_rgb color;

	color.r = 0.75 * amb.ratio * amb.color.r * obj.r;
	color.g = 0.75 * amb.ratio * amb.color.g * obj.g;
	color.b = 0.75 * amb.ratio * amb.color.b * obj.b;
	return (color);
}
static t_rgb	compute_defuse(t_hit hit, t_light source)
{
	t_rgb color;
	t_vec3 light_dir;
	double	angle;

	light_dir = vec3_norm(vec3_subtract(source.pos, hit.point));
	angle = fmax(0, vec3_dot(hit.normal, light_dir));
	color.r = angle * source.ratio * source.color.r * hit.color.r;
	color.g = angle * source.ratio * source.color.g * hit.color.g;
	color.b = angle * source.ratio * source.color.b * hit.color.b;
	return (color);
}

static t_rgb compute_spacular(t_hit hit, t_light source, t_cam cam)
{
	t_rgb color;
	t_vec3 ref_vec;
	t_vec3 light_dir;
	double	angle;
	double	shininess;

	light_dir = vec3_norm(vec3_subtract(source.pos, hit.point));
	ref_vec = vec3_scale(2 * vec3_dot(hit.normal, light_dir), hit.normal);
	ref_vec = vec3_subtract(ref_vec, light_dir);
	angle = fmax(0, vec3_dot(ref_vec, vec3_norm(vec3_subtract(cam.pos, hit.point))));
	shininess = pow(angle, 20);
	color.r = shininess * source.ratio * source.color.r;
	color.g = shininess * source.ratio * source.color.g;
	color.b = shininess * source.ratio * source.color.b;
	return color;
}

t_rgb	compute_color(t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	diffuse;
	t_rgb	spacular;
	t_rgb	combined;

	if (hit.hit == false)
		return (int_to_rgb(BG_COLOR));
	amb = compute_amb(hit.color, data->scene.amb_light);
	if (is_shadow(hit, data) == true)
		return rgb(amb.r, amb.g, amb.b);
	diffuse = compute_defuse(hit, data->scene.light);
	spacular = compute_spacular(hit, data->scene.light, data->scene.cam);
	combined = rgb(
			spacular.r + amb.r + diffuse.r,
			spacular.g + amb.g + diffuse.g,
			spacular.b + amb.b + diffuse.b
			);
	return combined;
}

