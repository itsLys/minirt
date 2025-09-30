/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:40:41 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:44:07 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	sample_sp_color(t_hit hit)
{
	t_vec2 coords;
	t_vec3 local;
	double	theta;
	double	phi;

	local = world_to_local(hit, hit.obj->coords);
	theta = atan2(local.z, local.x);
	phi = acos(local.y);
	coords.x = (theta + M_PI) / (2 * M_PI);
	coords.y = phi / M_PI;
	coords.x = fmod(coords.x * 2.0, 1.0);
	coords.y = fmod(coords.y * 2.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys
	return sample_tx_color(coords, hit.obj->tx);
}

t_rgb	sample_cy_color(t_hit hit, t_cy *cy)
{
	t_vec3 local;
	double	tetha;
	t_vec2	coords;

	local = world_to_local(hit, hit.obj->coords);
	tetha = atan2(local.z, local.x);
	coords.x = fmod((tetha / (2 * M_PI)), 1.0) ;
	coords.y = 1.0 - (local.y + cy->h / 2.0) / cy->h;
	coords.x = fmod(coords.x * 3.0, 1.0);
	coords.y = fmod(coords.y * 3.0, 1.0); // FIX: turn into dynamic texture number, increase and decrease via keys
	return sample_tx_color(coords, hit.obj->tx);
}

t_rgb	sample_pl_color(t_hit hit)
{
	t_vec3 local;
	t_vec2 coords;

	local = world_to_local(hit, hit.obj->coords);
	coords.x = local.x / hit.obj->tx->width;
	coords.y = local.z / hit.obj->tx->height;
	coords.x = fabs(fmod(coords.x * 10.0, 1.0));
	coords.y = fabs(fmod(coords.y * 10.0, 1.0)); // FIX: turn into dynamic texture number, increase and decrease via keys
	return sample_tx_color(coords, hit.obj->tx);
}
