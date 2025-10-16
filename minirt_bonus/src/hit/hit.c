/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:09:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/16 11:07:41 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	resolve_sp_hit(t_ray ray, t_obj *obj, t_sp *sp, t_quad quad)
{
	t_hit	hit;

	(void)sp;
	hit.inside = false;
	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_norm(vec3_subtract(hit.point, obj->pos));
	if (vec3_dot(ray.dir, hit.normal) > 0)
	{
		hit.inside = true;
		hit.normal = vec3_negate(hit.normal);
	}
	return (hit);
}

t_hit	resolve_cy_hit(t_ray ray, t_obj *obj, t_cy *cy, t_quad quad)
{
	t_hit	hit;

	hit.inside = false;
	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	if (quad.t1 > 0)
		hit.hit = check_cy_height_intersect(quad.t1, ray, obj, cy);
	if (quad.t2 > 0 && (hit.hit == false || (hit.hit == true && quad.t1 < EPS)))
	{
		hit.t = quad.t2;
		hit.hit = check_cy_height_intersect(quad.t2, ray, obj, cy);
		hit.inside = true;
	}
	if (hit.hit == false)
		return (hit);
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_scale(vec3_dot(vec3_subtract(hit.point, obj->pos),
				obj->coords.up),
			obj->coords.up);
	hit.normal = vec3_subtract(hit.point, vec3_add(obj->pos, hit.normal));
	hit.normal = vec3_norm(hit.normal);
	if (hit.inside)
		hit.normal = vec3_negate(hit.normal);
	return (hit);
}

t_hit	resolve_pl_hit(t_ray ray, t_obj *obj, double a, double b)
{
	double	t;
	t_hit	hit;

	hit.inside = false;
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
	{
		hit.inside = true;
		hit.normal = vec3_scale(-1, hit.normal);
	}
	return (hit);
}

t_hit	resolve_rc_hit(t_ray ray, t_obj *obj, double a, double b)
{
	double	t;
	t_hit	hit;

	hit.inside = false;
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
	hit.hit = check_rc_height_length(obj, hit.point);
	if (hit.hit == false)
		return ((t_hit){.hit = false});
	hit.normal = obj->coords.up;
	if (vec3_dot(ray.dir, hit.normal) > 0)
	{
		hit.inside = true;
		hit.normal = vec3_scale(-1, hit.normal);
	}
	return (hit);
}

t_hit	resolve_cn_hit(t_ray ray, t_obj *obj, t_quad quad, t_cn *cn)
{
	t_hit	hit;

	hit.inside = false;
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
	if (hit.hit == false)
		return (hit);
	hit.point = vec3_add(ray.orig, vec3_scale(hit.t, ray.dir));
	hit.normal = cn_hit_normal(obj, hit.point, cn);
	if (vec3_dot(ray.dir, hit.normal) > 0)
	{
		hit.inside = true;
		hit.normal = vec3_negate(hit.normal);
	}
	return (hit);
}
