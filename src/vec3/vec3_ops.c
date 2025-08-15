/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/15 11:24:36 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 vec3(int x, int y, int z)
{
	t_vec3	v;

	v = {x, y, z};
	return (v);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)
}

double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double	l;

	l = vec3_len(v);
	return (vec3(v.x/l, v.y/l, v.z/l));
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.y * v2.z - (v1.z * v2.y);
	v.y = v1.z * v2.x - (v1.x * v2.z);
	v.z = v1.x * v2.y - (v1.y * v2.x);
	return (v);
}

