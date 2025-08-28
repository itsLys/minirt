/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:09:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/28 09:42:39 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy)
{
	t_vec3	check_height;
	double	q;

	check_height = vec3_scale(t, ray.dir);
	check_height = vec3_add(check_height, ray.orign);
	check_height = vec3_subtract(check_height, obj->pos);
	q = vec3_dot(check_height, cy->norm);
	if (q >= -cy->h/2.0 && q <= cy->h/2.0)
		return true;
	return false;
}

void	resolve_hit(t_hit *hit, t_quad quad)
{
	hit->hit = true;
	if (quad.t1 < EPS && quad.t2 < EPS)
		hit->hit = false;
	else if (quad.t1 < EPS)
		hit->t = quad.t2;
	else
		hit->t = quad.t1;
}

t_hit	resolve_sp_hit(t_ray ray, t_obj *obj, t_sp *sp, t_quad quad)
{
	t_hit	hit;

	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return (t_hit){.hit = false};
	hit.point = vec3_add(ray.orign, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_scale(1.0 / sp->r, vec3_subtract(hit.point, obj->pos));
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	return	hit;
}

t_hit	resolve_cy_hit(t_ray ray, t_obj *obj, t_cy *cy, t_quad quad)
{
	t_hit	hit;

	resolve_hit(&hit, quad);
	if (hit.hit == false)
		return (t_hit){.hit = false};
	hit.hit = check_cy_height_intersect(quad.t1, ray, obj, cy);
	if (hit.hit == false)
	{
		hit.t = quad.t2;
		hit.hit = check_cy_height_intersect(quad.t2, ray, obj, cy);
	}
	hit.point = vec3_add(ray.orign, vec3_scale(hit.t, ray.dir));
	hit.normal = vec3_subtract(hit.point, obj->pos);
	hit.normal = vec3_scale(vec3_dot(hit.normal, cy->norm), cy->norm);
	hit.normal = vec3_add(obj->pos, hit.normal);
	hit.normal = vec3_subtract(hit.point, hit.normal);
	hit.normal = vec3_norm(hit.normal);
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	return hit;
}

t_hit	resolve_pl_hit(t_pl *pl, t_ray ray, double a, double b)
{
	double	t;
	t_hit	hit;

	if (b < EPS && b > -EPS)
		return (t_hit){.hit = false};
	t = a / b;
	if (t < EPS)
		return (t_hit){.hit = false};
	else
		hit.hit = true;
	hit.t = t;
	hit.point = vec3_scale(hit.t, ray.dir);
	hit.point = vec3_add(ray.orign, hit.point);
	hit.normal = pl->norm; // fix it 	
	if (vec3_dot(ray.dir, hit.normal) > 0)
		hit.normal = vec3_negate(hit.normal);
	return hit;
}
