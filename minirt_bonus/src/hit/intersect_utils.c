/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:24:49 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 16:36:28 by yel-guad         ###   ########.fr       */
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
		|| b < -rc->length / 2.0 || b > rc->length / 2.0)
		return (false);
	return (true);
}
