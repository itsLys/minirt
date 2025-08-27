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

static t_rgb compute_defuse(t_hit hit, t_data *data)
{
	t_vec3	light_dir;
	t_light	light;
	t_rgb	rgb;
	double	dot;

	light = data->scene.light;
	light_dir = vec3_norm(vec3_subtract(light.pos, hit.point));
	dot = vec3_dot(hit.normal, light_dir);
	if (dot < 0 || is_shadow(hit, data))
		return (t_rgb) {0};
	rgb.r = (fmax(0.0, dot) * light.ratio * light.color.r * hit.color.r);
	rgb.g = (fmax(0.0, dot) * light.ratio * light.color.g * hit.color.g);
	rgb.b = (fmax(0.0, dot) * light.ratio * light.color.b * hit.color.b);
	return rgb;
}

t_rgb	compute_color(t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	defuse;

	if (hit.hit == false)
		return int_to_rgb(BG_COLOR);
	amb = compute_amb(hit.color, data->scene.amb_light);
	defuse = compute_defuse(hit, data);
	return rgb(amb.r + defuse.r,
			amb.g + defuse.g,
			amb.b + defuse.b);
}
