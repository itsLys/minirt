/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/14 16:06:31 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	record_hit(t_obj **obj, t_hit *hit, t_ray ray)
{
	while (*obj && (*obj)->type == T_LS)
		(*obj) = (*obj)->next;
	check_sp_intersect(obj, hit, ray);
	check_pl_intersect(obj, hit, ray);
	check_cy_intersect(obj, hit, ray);
	check_cn_intersect(obj, hit, ray);
	check_rc_intersect(obj, hit, ray);
}

t_vec2	compute_texture_ratio(t_hit hit)
{
	if (hit.obj->type == T_SP)
		return (sphere_ratio(hit, hit.obj->shape));
	else if (hit.obj->type == T_PL)
		return (plane_ratio(hit, hit.obj->shape));
	else if (hit.obj->type == T_CY)
		return (cylinder_ratio(hit, hit.obj->shape));
	else if (hit.obj->type == T_CN)
		return (cone_ratio(hit, hit.obj->shape));
	else if (hit.obj->type == T_RC)
		return (rectangle_ratio(hit, hit.obj->shape));
	return ((t_vec2){-1, -1});
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
	if (hit.hit && (hit.obj->tx || hit.obj->bmp))
	{
		coords = compute_texture_ratio(hit);
		if (hit.obj->tx)
			hit.color = sample_tx_color(coords, hit.obj->tx);
		hit.normal_bumped = hit.normal;
		if (hit.obj->bmp)
			apply_bump_map(&hit, coords);
	}
	return (compute_color(ray, hit, data));
}
