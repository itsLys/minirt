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

t_vec3	rotate(t_vec3 to_rot, t_vec3 axis, double angle)
{
	t_vec3	v_cos;
	t_vec3	cross_sin;
	t_vec3	axis_proj;
	t_vec3	result;

	v_cos = vec3_scale(cos(angle), to_rot);
	cross_sin = vec3_scale(sin(angle), vec3_cross(axis, to_rot));
	axis_proj = vec3_scale(vec3_dot(axis, to_rot), axis);
	axis_proj = vec3_scale(1.0 - cos(angle), axis_proj);
	result = vec3_add(v_cos, cross_sin);
	result = vec3_add(result, axis_proj);
	return (result);
}

t_vec3	translate(t_vec3 p, t_vec3 v)
{
	return (vec3_add(p, v));
}
