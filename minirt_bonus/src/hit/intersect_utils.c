/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:24:49 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/16 11:07:45 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_cn_height_intersect(double t, t_ray ray, t_obj *obj, t_cn *cn)
{
	t_vec3	check_height;
	double	q;

	check_height = vec3_scale(t, ray.dir);
	check_height = vec3_add(check_height, ray.orig);
	check_height = vec3_subtract(check_height, obj->pos);
	q = vec3_dot(check_height, obj->coords.up);
	if (0.0 <= q && cn->h >= q)
		return (true);
	return (false);
}

bool	check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy)
{
	t_vec3	check_height;
	double	q;

	check_height = vec3_scale(t, ray.dir);
	check_height = vec3_add(check_height, ray.orig);
	check_height = vec3_subtract(check_height, obj->pos);
	q = vec3_dot(check_height, obj->coords.up);
	if (q >= -cy->h / 2.0 && q <= cy->h / 2.0)
		return (true);
	return (false);
}

bool	check_rc_height_length(t_obj *obj, t_vec3 hitpoint)
{
	double	a;
	double	b;
	t_vec3	v;
	t_rc	*rc;

	rc = (t_rc *)obj->shape;
	v = vec3_subtract(hitpoint, obj->pos);
	a = fabs(vec3_dot(v, obj->coords.forward));
	b = fabs(vec3_dot(v, obj->coords.right));
	if (a < -rc->width / 2.0 || a > rc->width / 2.0
		|| b < -rc->height / 2.0 || b > rc->height / 2.0)
		return (false);
	return (true);
}

t_vec3	cn_hit_normal(t_obj *obj, t_vec3 point, t_cn *cn)
{
	t_vec3	normal;
	t_vec3	term1;
	t_vec3	term2;

	normal = vec3_subtract(point, obj->pos);
	term1 = vec3_scale(vec3_dot(normal, obj->coords.up), obj->coords.up);
	term2 = vec3_scale(cosf(cn->angle) * cosf(cn->angle), normal);
	normal = vec3_norm(vec3_subtract(term1, term2));
	return (normal);
}
