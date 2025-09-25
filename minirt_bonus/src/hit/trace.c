/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 16:50:27 by ihajji           ###   ########.fr       */
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

t_rgb	sample_sp_color(t_hit hit)
{
	t_vec2 coords;
	t_vec3 n;
	double	theta;
	double	phi;

	n.x = vec3_dot(hit.normal, hit.obj->coords.right);
	n.y = vec3_dot(hit.normal, hit.obj->coords.up);
	n.z = vec3_dot(hit.normal, hit.obj->coords.forward);
	theta = atan2(n.z, n.x);
	phi = acos(n.y);
	coords.x = (theta + M_PI) / (2 * M_PI);
	coords.y = phi / M_PI;
	coords.x = fmod(coords.x * 1.0, 1.0);
	coords.y = fmod(coords.y * 1.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys

	return sample_tx_color(coords, hit.obj->tx);
}

t_rgb	sample_cy_color(t_hit hit, t_cy *cy)
{
	t_vec3	S = vec3_cross(hit.obj->coords.forward, hit.obj->coords.up); // this is right, or maybe use it as forward
	t_vec3	V = vec3_subtract(hit.point, hit.obj->pos);
	double	y = vec3_dot(V, hit.obj->coords.up);
	t_vec3	R = vec3_scale(y, hit.obj->coords.up);
	R 		  = vec3_subtract(V, R);
	R 		  = vec3_norm(R);
	double	u_angle = atan2(vec3_dot(vec3_cross(S, R), hit.obj->coords.up), vec3_dot(R, S));
	t_vec2	coords;
	coords.x = fmod((u_angle / (2 * M_PI)), 1.0) ;
	coords.y = (y + cy->h / 2.0) / cy->h;

	coords.x = fmod(coords.x * 5.0, 1.0);
	coords.y = fmod(coords.y * 10.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys
							//
	return sample_tx_color(coords, hit.obj->tx);
}

t_rgb	sample_pl_color(t_hit hit)
{
	t_vec3	rel = vec3_subtract(hit.point, hit.obj->pos);


	double	x_local = vec3_dot(rel, hit.obj->coords.forward);
	double	y_local = vec3_dot(rel, hit.obj->coords.right);
	t_vec2 coords;


	coords.x = x_local / 50; // turn this into a dynamic number with events and keys
	coords.y = y_local / 50;
	coords.x = coords.x - floor(coords.x);
	coords.y = coords.y - floor(coords.y);

	return sample_tx_color(coords, hit.obj->tx);
}

t_rgb	sample_color(t_hit hit)
{
	if (hit.obj->type == T_SP)
		return sample_sp_color(hit);
	else if (hit.obj->type == T_PL)
		return sample_pl_color(hit);
	else if (hit.obj->type == T_CY)
		return sample_cy_color(hit, hit.obj->shape);
	else
		return hit.obj->color;
	// else if (hit.obj->type == T_CN)
	// 	return sample_cn_color(hit, data); FIX: implement cone
}

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_obj	*obj;

	hit.t = INFINITY;
	hit.hit = 0;
	hit.obj = NULL;
	obj = *(data->scene.obj_lst);
	record_hit(&obj, &hit, ray);
	if (hit.obj && hit.obj->tx)
		hit.color = sample_color(hit);
	return (compute_color(ray, hit, data));
}
