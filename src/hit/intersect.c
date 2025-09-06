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

t_hit    intersect_cy(t_ray ray, t_obj *obj, t_cy *cy)
{
	t_vec3	oc;
	t_quad	quad;

	oc = vec3_subtract(ray.orign, obj->pos);
	quad.a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy->norm), 2); //  x*x faster than pow(x, 2)
	quad.b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(oc, cy->norm) * vec3_dot(ray.dir, cy->norm));
	quad.c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->norm), 2) - cy->r * cy->r; // Same 'x*x faster than pow(x, 2)'
	solve_quadratic(&quad);
	return (resolve_cy_hit(ray, obj, cy, quad));
}

t_hit    intersect_pl(t_ray ray, t_obj *obj, t_pl *pl)
{
	double	a;
	double	b;

	a = vec3_dot(vec3_subtract(obj->pos, ray.orign), pl->norm);
	b = vec3_dot(ray.dir, pl->norm);
	return (resolve_pl_hit(pl, ray, a, b));
}
