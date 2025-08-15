/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 16:02:13 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// t_vec3	vec3_norm(t_vec3 v)
// {
//
// }
//
// t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
// {
//
// }
//
// double	vec3_dot(t_vec3 v1, t_vec3 v2)
// {
//
// }
