/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:04:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:36:22 by ihajji           ###   ########.fr       */
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
	dot = vec3_dot(ray.dir, cy->norm);
	quad.a = vec3_dot(ray.dir, ray.dir) - (dot * dot);
	quad.b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(oc, cy->norm)
			* vec3_dot(ray.dir, cy->norm));
	dot = vec3_dot(oc, cy->norm);
	quad.c = vec3_dot(oc, oc) - (dot * dot) - cy->r * cy->r;
	solve_quadratic(&quad);
	return (resolve_cy_hit(ray, obj, cy, quad));
}

t_hit	intersect_pl(t_ray ray, t_obj *obj, t_pl *pl)
{
	double	a;
	double	b;

	a = vec3_dot(vec3_subtract(obj->pos, ray.orign), pl->norm);
	b = vec3_dot(ray.dir, pl->norm);
	return (resolve_pl_hit(pl, ray, a, b));
}
