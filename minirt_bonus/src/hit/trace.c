/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:17:47 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_sp_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_SP)
	{
		tmp = intersect_sp(ray, *obj, (t_sp *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_pl_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_PL)
	{
		tmp = intersect_pl(ray, *obj, (t_pl *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_cy_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_CY)
	{
		tmp = intersect_cy(ray, *obj, (t_cy *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}
void	check_cn_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_CN)
	{
		tmp = intersect_cn(ray, *obj, (t_cn *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	record_hit(t_obj **obj, t_hit *hit, t_ray ray)
{
	while (*obj && (*obj)->type == T_LS)
		(*obj) = (*obj)->next;
	check_sp_intersect(obj, hit, ray);
	check_pl_intersect(obj, hit, ray);
	check_cy_intersect(obj, hit, ray);
	check_cn_intersect(obj, hit, ray);
}

t_rgb	sample_sp_color(t_hit hit, t_data *data)
{
	t_vec3	normal = hit.normal; // NORMALIZE??
	double	thetha = atan2(normal.z, normal.x);
	double	phi = acos(normal.y);
	double	u = (thetha + M_PI) / (2 * M_PI);
	double	v = phi / M_PI;
	char	*color;

	t_int_vec2 tx_index;

	tx_index.x = u * (data->texture.width - 1);
	tx_index.y = v * (data->texture.height - 1);
	color = data->texture.addr + tx_index.y * data->texture.line_len + tx_index.x * (data->texture.bpp / 8);
	return int_to_rgb(*((int *)color));
}

t_rgb	sample_cy_color(t_hit hit, t_cy *cy, t_data *data)
{
	// TODO: optimize address reading, read once
	t_vec3	S = vec3_cross(vec3(1, 0, 0), hit.obj->coords.up);
	t_vec3	V = vec3_subtract(hit.point, hit.obj->pos);
	double	y = vec3_dot(V, hit.obj->coords.up);
	t_vec3	R = vec3_scale(y, hit.obj->coords.up);
	R 		  = vec3_subtract(V, R);
	R 		  = vec3_norm(R);
	double	u_angle = atan2(vec3_dot(vec3_cross(S, R), hit.obj->coords.up), vec3_dot(R, S));
	double u = fmod((u_angle / (2 * M_PI)), 1.0) ;
	double v = (y + cy->h / 2.0) / cy->h;
	char	*color;
	t_int_vec2 tx_index;

	tx_index.x = u * (data->texture.width - 1);
	tx_index.y = v * (data->texture.height - 1);
	color = data->texture.addr + tx_index.y * data->texture.line_len + tx_index.x * (data->texture.bpp / 8);
	return int_to_rgb(*((int *)color));
}

// t_rgb	sample_pl_color(t_hit hit, t_data *data)
// {
// 	char	*color;
// 	t_int_vec2 tx_index;
//
// 	tx_index.x = u * (data->texture.width - 1);
// 	tx_index.y = v * (data->texture.height - 1);
// 	color = data->texture.addr + tx_index.y * data->texture.line_len + tx_index.x * (data->texture.bpp / 8);
// 	return int_to_rgb(*((int *)color));
// 	// BUG: segfaults
// }

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_obj	*obj;

	hit.t = INFINITY;
	hit.hit = 0;
	hit.obj = NULL;
	obj = *(data->scene.obj_list);
	record_hit(&obj, &hit, ray);
	if (hit.obj && hit.obj->type == T_CY)
		hit.color = sample_cy_color(hit, hit.obj->shape, data);
	return (compute_color(ray, hit, data));
}
