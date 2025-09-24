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

t_rgb	sample_sp_color(t_hit hit)
{
	t_vec3	normal = hit.normal; // NORMALIZE??
	double nx = vec3_dot(normal, hit.obj->coords.right); // local X (front)
	double ny = vec3_dot(normal, hit.obj->coords.up); // local Y (up)
	double nz = vec3_dot(normal, hit.obj->coords.forward); // local Z (right)
	double	thetha = atan2(nz, nx);
	double	phi = acos(ny);
	double	u = (thetha + M_PI) / (2 * M_PI);
	double	v = phi / M_PI;
	char	*color;

	t_int_vec2 tx_index;

	u = fmod(u * 1.0, 1.0);
	v = fmod(v * 1.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys
											  //
	tx_index.x = u * (hit.obj->tx->width - 1);
	tx_index.y = v * (hit.obj->tx->height - 1);

											   //
	color = hit.obj->tx->img.addr + tx_index.y * hit.obj->tx->img.line_len + tx_index.x * (hit.obj->tx->img.bpp / 8); // could turn it into a func like put_pixel
	return int_to_rgb(*((int *)color));
}

t_rgb	sample_cy_color(t_hit hit, t_cy *cy)
{
	// TODO: optimize address reading, read once
	t_vec3	S = vec3_cross(hit.obj->coords.forward, hit.obj->coords.up);
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

	u = fmod(u * 5.0, 1.0);
	v = fmod(v * 10.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys
							//
	tx_index.x = u * (hit.obj->tx->width - 1);
	tx_index.y = v * (hit.obj->tx->height - 1);
	color = hit.obj->tx->img.addr + tx_index.y * hit.obj->tx->img.line_len + tx_index.x * (hit.obj->tx->img.bpp / 8); // could turn it into a func like put_pixel
	return int_to_rgb(*((int *)color));
}

t_rgb	sample_pl_color(t_hit hit)
{
	t_vec3	rel = vec3_subtract(hit.point, hit.obj->pos);


	double	x_local = vec3_dot(rel, hit.obj->coords.forward);
	double	y_local = vec3_dot(rel, hit.obj->coords.right);

	double u = x_local / 50; // turn this into a dynamic number with events and keys
	double v = y_local / 50;
	u = u - floor(u);  // equivalent to fmod(u, 1.0) but works for negatives
	v = v - floor(v);
	char	*color;
	t_int_vec2 tx_index;

	tx_index.x = u * (hit.obj->tx->width - 1);
	tx_index.y = v * (hit.obj->tx->height - 1);
	color = hit.obj->tx->img.addr + tx_index.y * hit.obj->tx->img.line_len + tx_index.x * (hit.obj->tx->img.bpp / 8); // could turn it into a func like put_pixel
	return int_to_rgb(*((int *)color));
	// TODO: add dynamic texutre from config file,
	// add dynamic number of tiles per hit point (what??)
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
	// 	return sample_cn_color(hit, data);
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
