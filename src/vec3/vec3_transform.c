/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:31:12 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 10:37:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// BUG: fix
t_vec3	rotate(t_vec3 to_rot, t_vec3 rot_around, double	angle)
{
	t_vec3	v_cos = vec3_scale(cosf(angle), to_rot);
	t_vec3	cross_sin = vec3_scale(sinf(angle), vec3_cross(rot_around, to_rot));
	t_vec3 kkv = vec3_scale(vec3_dot(rot_around, to_rot), to_rot);
	kkv = vec3_scale(1.0 - cosf(angle), kkv);

	t_vec3 new;

	new = vec3_add(v_cos, cross_sin);
	new = vec3_add(new, kkv);
	return new;
}

t_vec3	translate(t_vec3 p, t_vec3 v)
{
	return (vec3_add(p, v));
}
