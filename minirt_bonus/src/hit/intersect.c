/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:04:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:09:05 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersect_sp(t_ray ray, t_obj *obj, t_sp *sp)
{
	t_quad	quad;
	t_vec3	oc;

	oc = vec3_subtract(ray.orign, obj->pos);
	quad.a = 1;
	quad.b = 2 * vec3_dot(ray.dir, oc);
	quad.c = vec3_dot(oc, oc) - sp->r * sp->r;
	solve_quadratic(&quad);
	return (resolve_sp_hit(ray, obj, sp, quad));
}

t_hit	intersect_cy(t_ray ray, t_obj *obj, t_cy *cy)
{
	t_vec3	oc;
	t_quad	quad;
	double	dot;

	oc = vec3_subtract(ray.orign, obj->pos);
	dot = vec3_dot(ray.dir, obj->coords.up);
	quad.a = vec3_dot(ray.dir, ray.dir) - (dot * dot);
	quad.b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(oc, obj->coords.up)
			* vec3_dot(ray.dir, obj->coords.up));
	dot = vec3_dot(oc, obj->coords.up);
	quad.c = vec3_dot(oc, oc) - (dot * dot) - cy->r * cy->r;
	solve_quadratic(&quad);
	return (resolve_cy_hit(ray, obj, cy, quad));
}

t_hit	intersect_pl(t_ray ray, t_obj *obj, t_pl *pl)
{
	(void) pl; // for now
	double	a;
	double	b;

	a = vec3_dot(vec3_subtract(obj->pos, ray.orign), obj->coords.up);
	b = vec3_dot(ray.dir, obj->coords.up);
	return (resolve_pl_hit(ray, obj, a, b));
}

t_hit    intersect_cn(t_ray ray, t_obj *obj, t_cn *cn)
{
    t_quad    quad;
    t_vec3    oc;
    double    cos_angle;
    double    dir_dot_norm;
    double    oc_dot_norm;
    
    cos_angle = cosf(cn->angle);
    oc = vec3_subtract(ray.orign, obj->pos);
    dir_dot_norm = vec3_dot(ray.dir, obj->coords.up);
    oc_dot_norm = vec3_dot(oc, obj->coords.up);

    quad.a = cos_angle * cos_angle * vec3_dot(ray.dir, ray.dir) - dir_dot_norm * dir_dot_norm;
    quad.b = cos_angle * cos_angle * vec3_dot(oc, ray.dir);
    quad.b = 2 *(quad.b - oc_dot_norm * dir_dot_norm);
    quad.c = cos_angle * cos_angle * vec3_dot(oc, oc);
    quad.c -= oc_dot_norm * oc_dot_norm;
    solve_quadratic(&quad);
    return (resolve_cn_hit(ray, obj, quad, cn));
}
