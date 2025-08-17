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

t_vec3 vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double	l;

	
	l = vec3_len(v);
	if (l == 0.0)
		return vec3(0, 0, 0);
	return (vec3(v.x/l, v.y/l, v.z/l));
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;

	return (v);
}

t_vec3	vec3_scale(double s, t_vec3 vec)
{
	t_vec3	res;

	res.x = vec.x * s;
	res.y = vec.y * s;
	res.z = vec.z * s;
	return (res);
}

t_vec3 vec3_subtract(t_vec3 v1, t_vec3 v2)
{
	t_vec3 res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return res;
}

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return res;
}

t_vec3 vec3_negate(t_vec3 v)
{
	t_vec3 res;

	res.x = v.x * -1;
	res.y = v.y * -1;
	res.z = v.z * -1;
	return res;
}
