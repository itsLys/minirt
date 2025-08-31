/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:27:02 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 10:30:07 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double	length;


	length = vec3_len(v);
	if (length == 0.0)
		return vec3(0, 0, 0);
	return (vec3(v.x/length, v.y/length, v.z/length));
}
