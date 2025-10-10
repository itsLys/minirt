/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:34:34 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:35:05 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "types.h"

t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_norm(t_vec3 v);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
double	vec3_len(t_vec3 v);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_scale(double s, t_vec3 vec);
t_vec3	vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_negate(t_vec3 v);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	rotate(t_vec3 to_rot, t_vec3 rot_around, double angle);
t_vec3	translate(t_vec3 p, t_vec3 v);

#endif // !VEC3_H
