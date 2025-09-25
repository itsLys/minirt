/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 16:14:20 by ihajji           ###   ########.fr       */
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

static bool	is_shadow(t_hit hit, t_obj *light, t_data *data)
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

static inline t_rgb	compute_amb(t_rgb obj, t_amb_light amb)
{
	t_rgb color;

	color.r = amb.ratio * amb.color.r * obj.r;
	color.g = amb.ratio * amb.color.g * obj.g;
	color.b = amb.ratio * amb.color.b * obj.b;
	return (color);
}
static t_rgb	compute_defuse(t_hit hit, t_obj *light_obj, t_light *light)
{
	t_rgb color;
	t_vec3 light_dir;
	double	angle;

	light_dir = vec3_norm(vec3_subtract(light_obj->pos, hit.point));
	angle = fmax(0, vec3_dot(hit.normal, light_dir));
	color.r = angle * light->ratio * light_obj->color.r * hit.color.r;
	color.g = angle * light->ratio * light_obj->color.g * hit.color.g;
	color.b = angle * light->ratio * light_obj->color.b * hit.color.b;
	return (color);
}

static t_rgb compute_spacular(t_hit hit, t_obj *l_obj, t_light *light, t_cam cam)
{
	t_rgb color;
	t_vec3 ref_vec;
	t_vec3 light_dir;
	double	angle;
	double	shininess;

	light_dir = vec3_norm(vec3_subtract(l_obj->pos, hit.point));
	ref_vec = vec3_scale(2 * vec3_dot(hit.normal, light_dir), hit.normal);
	ref_vec = vec3_subtract(ref_vec, light_dir);
	angle = fmax(0, vec3_dot(ref_vec, vec3_norm(vec3_subtract(cam.pos, hit.point))));
	shininess = pow(angle, hit.obj->shine);
	color.r = hit.obj->ref * shininess * light->ratio * l_obj->color.r;
	color.g = hit.obj->ref * shininess * light->ratio * l_obj->color.g;
	color.b = hit.obj->ref * shininess * light->ratio * l_obj->color.b;
	return color;
}

t_rgb compute_light(t_hit hit, t_obj *l_obj, t_light *light, t_data *data)
{
	t_rgb	diffuse;
	t_rgb	spacular;
	t_rgb	color;

	if (is_shadow(hit, l_obj, data) == true)
		return rgb(0, 0, 0);
	diffuse = compute_defuse(hit, l_obj, light);
	spacular = compute_spacular(hit, l_obj, light, data->scene.cam);
	color.r = diffuse.r + spacular.r;
	color.g = diffuse.g + spacular.g;
	color.b = diffuse.b + spacular.b;
	return color;
}

t_rgb sample_color(t_vec2 coords, t_texture *tx)
{
	int	x;
	int	y;

	x = coords.x * (tx->width - 1);
	y = coords.x * (tx->height - 1);

	return img_get_pixel(tx->img, x, y);
}

t_rgb	sample_bg_color(int x, int y, t_texture *tx)
{
	t_vec2	coords;

	coords.x = x / (WIDTH - 1.0);
	coords.y = y / (HEIGHT - 1.0);

	coords.x = fmod(coords.x * 1.0, 1.0);
	coords.y = fmod(coords.y * 1.0, 1.0);

	return sample_color(coords,  tx);
}

t_rgb	compute_lights(t_hit hit, t_data *data)
{
	t_rgb	sum;
	t_rgb	light;
	t_obj	*obj;

	sum = int_to_rgb(0);
	obj = *(data->scene.obj_lst);
	while (obj)
	{
		if (obj && obj->type == T_LS)
		{
			light = compute_light(hit, obj, (t_light *)(obj->shape), data);
			sum = rgb_add(sum, light);
		}
		obj = obj->next;
	}
	return sum;
}

t_rgb	compute_bg_color(int x, int y, t_amb_light amb)
{
	if (amb.tx)
		return rgb_scale(amb.ratio, sample_bg_color(x, y, amb.tx));
	return rgb_scale(amb.ratio, amb.color);

}

t_rgb	compute_color(t_ray ray, t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	combined;
	t_rgb	sum;

	if (hit.hit == false)
		return compute_bg_color(ray.px.x, ray.px.y, data->scene.amb);
	amb = compute_amb(hit.color, data->scene.amb);
	sum = compute_lights(hit, data);
	combined = rgb_add(sum, amb);
	return combined;
}
