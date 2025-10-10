/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:24:49 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/10 18:25:03 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_cn_height_intersect(double t, t_ray ray, t_obj *obj, t_cn *cn)
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

int	check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy)
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
