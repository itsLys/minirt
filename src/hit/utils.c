/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:09:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/23 12:17:21 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
