/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:41:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	compute_bg_color(int x, int y, t_amb_light amb)
{
	if (amb.tx)
		return (rgb_scale(amb.ratio, sample_bg_color(x, y, amb.tx)));
	return (rgb_scale(amb.ratio, amb.color));
}

t_rgb	compute_color(t_ray ray, t_hit hit, t_data *data)
{
	t_rgb	amb;
	t_rgb	combined;
	t_rgb	sum;

	if (hit.hit == false)
		return (compute_bg_color(ray.px.x, ray.px.y, data->scene.amb));
	amb = compute_amb(hit.color, data->scene.amb);
	sum = compute_lights(hit, data);
	combined = rgb_add(sum, amb);
	return (combined);
}
