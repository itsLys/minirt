/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:37:57 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 10:28:49 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	compute_amb(t_rgb obj, t_amb_light amb)
{
	t_rgb	color;

	color.r = amb.ratio * amb.color.r * obj.r;
	color.g = amb.ratio * amb.color.g * obj.g;
	color.b = amb.ratio * amb.color.b * obj.b;
	return (color);
}

t_rgb	compute_defuse(t_hit hit, t_obj *light_obj, t_light *light)
{
	t_rgb	color;
	t_vec3	light_dir;
	double	angle;

	light_dir = vec3_norm(vec3_subtract(light_obj->pos, hit.point));
	angle = fmax(0, vec3_dot(hit.normal, light_dir));
	color.r = angle * light->ratio * light_obj->color.r * hit.color.r;
	color.g = angle * light->ratio * light_obj->color.g * hit.color.g;
	color.b = angle * light->ratio * light_obj->color.b * hit.color.b;
	return (color);
}

t_rgb	compute_spacular(t_hit hit, t_obj *l_obj, t_light *light, t_cam cam)
{
	t_rgb	color;
	t_vec3	ref_vec;
	t_vec3	light_dir;
	double	angle;
	double	shininess;

	light_dir = vec3_norm(vec3_subtract(l_obj->pos, hit.point));
	ref_vec = vec3_scale(2 * vec3_dot(hit.normal, light_dir), hit.normal);
	ref_vec = vec3_subtract(ref_vec, light_dir);
	angle = fmax(0, vec3_dot(ref_vec, vec3_norm(vec3_subtract(cam.pos,
						hit.point))));
	shininess = pow(angle, hit.obj->shine);
	color.r = hit.obj->ref * shininess * light->ratio * l_obj->color.r;
	color.g = hit.obj->ref * shininess * light->ratio * l_obj->color.g;
	color.b = hit.obj->ref * shininess * light->ratio * l_obj->color.b;
	return (color);
}

t_rgb	compute_light(t_hit hit, t_obj *l_obj, t_light *light, t_data *data)
{
	t_rgb	diffuse;
	t_rgb	spacular;
	t_rgb	color;

	if (is_shadow(hit, l_obj, data) == true)
		return (rgb(0, 0, 0));
	diffuse = compute_defuse(hit, l_obj, light);
	spacular = compute_spacular(hit, l_obj, light, data->scene.cam);
	color.r = diffuse.r + spacular.r;
	color.g = diffuse.g + spacular.g;
	color.b = diffuse.b + spacular.b;
	return (color);
}

t_rgb	compute_lights(t_hit hit, t_data *data)
{
	t_rgb	sum;
	t_rgb	light;
	t_obj	*obj;

	sum = int_to_rgb(0);
	obj = *(data->scene.obj_lst);
	while (obj && obj->type == T_LS)
	{
		light = compute_light(hit, obj, (t_light *)(obj->shape), data);
		sum = rgb_add(sum, light);
		obj = obj->next;
	}
	return (sum);
}
