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

static bool	is_shadow(t_hit hit, t_obj *light, t_data *data)
{
	t_hit	tmp;
	t_obj	*obj;
	t_ray	ray;
	double	light_distance;

	ray.orign = hit.point;
	ray.dir = vec3_subtract(light->pos, hit.point);
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

static inline t_rgb	compute_amb(t_rgb obj, t_amb_light amb)
{
	t_rgb color;

	color.r = 0.75 * amb.ratio * amb.color.r * obj.r;
	color.g = 0.75 * amb.ratio * amb.color.g * obj.g;
	color.b = 0.75 * amb.ratio * amb.color.b * obj.b;
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

	// printf("type?:	");
	// print_obj_type(hit.obj);
	// print_vec3(hit.obj->pos);
	// printf("\n");
	// printf("shine:	%d\n", hit.obj->shine);
	// printf("ref:	%lf\n", hit.obj->reflect);
	light_dir = vec3_norm(vec3_subtract(l_obj->pos, hit.point));
	ref_vec = vec3_scale(2 * vec3_dot(hit.normal, light_dir), hit.normal);
	ref_vec = vec3_subtract(ref_vec, light_dir);
	angle = fmax(0, vec3_dot(ref_vec, vec3_norm(vec3_subtract(cam.pos, hit.point))));
	shininess = pow(angle, hit.obj->shine);
	// shininess = pow(angle, 25);
	color.r = hit.obj->reflect * shininess * light->ratio * l_obj->color.r;
	color.g = hit.obj->reflect * shininess * light->ratio * l_obj->color.g;
	color.b = hit.obj->reflect * shininess * light->ratio * l_obj->color.b;
	return color;
}

t_rgb compute_light(t_hit hit, t_obj *l_obj, t_light *light, t_data *data)
{
	t_rgb	diffuse;
	t_rgb	spacular;
	t_rgb	color;
	// t_rgb 	amb;
	//
	// amb = data->scene.amb_light.color;
	if (is_shadow(hit, l_obj, data) == true)
		return rgb(0, 0, 0);
	diffuse = compute_defuse(hit, l_obj, light);
	spacular = compute_spacular(hit, l_obj, light, data->scene.cam);
	color.r = diffuse.r + spacular.r;
	color.g = diffuse.g + spacular.g;
	color.b = diffuse.b + spacular.b;
	return color;
}

t_rgb	sample_color(t_ray ray, t_data *data)
{
	t_vec2	px_co;
	t_int_vec2	tx_index;
	char *color;

	px_co.x = ray.pixel.x / (WIDTH - 1.0);
	px_co.y = ray.pixel.y / (HEIGHT - 1.0);

	tx_index.x = px_co.x * (data->texture.width - 1);
	tx_index.y = px_co.y * (data->texture.height - 1);

	color = data->texture.addr + tx_index.y * data->texture.line_len + tx_index.x * (data->texture.bpp / 8);
	return int_to_rgb(*((int *)color));
	// pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));

}

t_rgb	compute_color(t_ray ray, t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	combined;
	t_rgb	light;
	t_rgb	sum;
	t_obj	*obj;
	(void) ray;

	if (hit.hit == false)
		// return (sample_color(ray, data));
		// return int_to_rgb(BG_COLOR);
		return rgb_scale(data->scene.amb_light.ratio, data->scene.amb_light.color);
	amb = compute_amb(hit.color, data->scene.amb_light);
	obj = *(data->scene.obj_list);
	sum = (t_rgb) {0, 0, 0};
	while (obj)
	{
		if (obj && obj->type == T_LS)
		{
			light = compute_light(hit, obj, (t_light *)(obj->shape), data);
			sum.r += light.r;
			sum.g += light.g;
			sum.b += light.b;
		}
		obj = obj->next;
	}
	combined = rgb(sum.r + amb.r, sum.g + amb.g, sum.b + amb.b);
	return combined;
}

