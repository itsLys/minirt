/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:09:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/12 11:00:23 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resolve_hit(t_hit *hit, t_quad quad)
{
	hit->hit = true;
	if (quad.t1 < EPS && quad.t2 < EPS)
		hit->hit = false;
	else if (quad.t1 > EPS)
		hit->t = quad.t1;
	else
		hit->t = quad.t2;
}

t_hit	resolve_sp_hit(t_ray ray, t_obj *obj, t_sp *sp, t_quad quad)
{
	t_hit	hit;

	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_scale(1.0 / sp->r, vec3_subtract(hit.point, obj->pos));
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	return (hit);
}

t_hit	resolve_cy_hit(t_ray ray, t_obj *obj, t_cy *cy, t_quad quad)
{
	t_hit	hit;
	int		f;

	f = 0;
	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	if (quad.t1 > 0)
		hit.hit = check_cy_height_intersect(quad.t1, ray, obj, cy);
	if (quad.t2 > 0 && (hit.hit == false || (hit.hit == true && quad.t1 < EPS)))
	{
		hit.t = quad.t2;
		hit.hit = check_cy_height_intersect(quad.t2, ray, obj, cy);
		f = 1;
	}
	if (hit.hit == false)
		return (hit);
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_scale(vec3_dot(vec3_subtract(hit.point, obj->pos),
				obj->coords.up), obj->coords.up);
	hit.normal = vec3_subtract(hit.point, vec3_add(obj->pos, hit.normal));
	hit.normal = vec3_norm(hit.normal);
	if (f)
		hit.normal = vec3_negate(hit.normal);
	return (hit);
}

t_hit	resolve_pl_hit(t_ray ray, t_obj *obj, double a, double b)
{
	double	t;
	t_hit	hit;

	if (b < EPS && b > -EPS)
		return ((t_hit){.hit = false});
	t = a / b;
	if (t < EPS)
		return ((t_hit){.hit = false});
	else
		hit.hit = true;
	hit.t = t;
	hit.point = vec3_scale(hit.t, ray.dir);
	hit.point = vec3_add(ray.orig, hit.point);
	hit.normal = obj->coords.up;
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_scale(-1, hit.normal);
	return (hit);
}

t_hit	resolve_cn_hit(t_ray ray, t_obj *obj, t_quad quad, t_cn *cn)
{
	t_vec3	term1;
	t_vec3	term2;
	t_hit	hit;

	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	if (quad.t1 > 0)
		hit.hit = check_cn_height_intersect(quad.t1, ray, obj, cn);
	if (quad.t2 > 0 && (hit.hit == false || (hit.hit == true && quad.t1 < EPS)))
	{
		hit.t = quad.t2;
		hit.hit = check_cn_height_intersect(quad.t2, ray, obj, cn);
	}
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_subtract(hit.point, obj->pos);
	term1 = vec3_scale(vec3_dot(hit.normal, obj->coords.up), obj->coords.up);
	term2 = vec3_scale(cosf(cn->angle) * cosf(cn->angle), hit.normal);
	hit.normal = vec3_norm(vec3_subtract(term1, term2));
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	return (hit);
}
