/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/23 13:35:03 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// defuse = max(0, dot(normal, light_dir)) * light_color * intensity;
// color = amb + deffuse (+ phong later);
t_rgb compute_defuse(t_hit hit, t_vec3 light_pos, t_rgb color, double ratio)
{
	t_vec3	light_dir = vec3_norm(vec3_subtract(light_pos, hit.point));
	t_vec3	normal = hit.normal;
	double	dot = vec3_dot(normal, light_dir);
	t_rgb rgb;
	rgb.r = (fmax(0.0, dot) * ratio * color.r * hit.color.r);
	rgb.g = (fmax(0.0, dot) * ratio * color.g * hit.color.g);
	rgb.b = (fmax(0.0, dot) * ratio * color.b * hit.color.b);
	return rgb;
}

t_rgb	compute_color(t_hit hit, t_light amb_light, t_light light)
{
	// (void) light;
	t_rgb	amb;
	t_rgb	defuse;
	t_rgb 	color;

	if (hit.hit == false)
		return int_to_rgb(BG_COLOR);
	amb = compute_amb(hit.color, amb_light);
	defuse = compute_defuse(hit, light.pos, light.color, light.ratio);
	color.r = (amb.r + defuse.r);
	color.g = (amb.g + defuse.g);
	color.b = (amb.b + defuse.b);
	return color;
}
