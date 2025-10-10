/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/10 09:14:09 by yel-guad         ###   ########.fr       */
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
// TODO: refactor this since the performance boost in negligible

void	record_hit(t_obj **obj, t_hit *hit, t_ray ray)
{
	while (*obj && (*obj)->type == T_LS)
		(*obj) = (*obj)->next;
	check_sp_intersect(obj, hit, ray);
	check_pl_intersect(obj, hit, ray);
	check_cy_intersect(obj, hit, ray);
	check_cn_intersect(obj, hit, ray);
}

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_obj	*obj;
	t_vec2	coords;

	hit.t = INFINITY;
	hit.hit = 0;
	hit.obj = NULL;
	obj = *(data->scene.obj_lst);
	record_hit(&obj, &hit, ray);
	if (hit.hit)
	{
		if (hit.obj->tx || hit.obj->bmp)
			coords = compute_texture_ratio(hit);
		if (hit.obj->tx)
			hit.color = sample_tx_color(coords, hit.obj->tx);
		if (hit.obj->bmp)
			apply_bump_map(&hit, coords);
	}
	return (compute_color(ray, hit, data));
}
