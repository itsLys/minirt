/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_ratio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:14:21 by yel-guad          #+#    #+#             */
/*   Updated: 2025/10/19 15:29:24 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec2	sphere_ratio(t_hit hit, t_sp *sp)
{
	t_vec2	coords;
	t_vec3	local;
	double	theta;
	double	phi;

	local = world_to_local(hit, hit.obj->coords);
	theta = atan2(local.z, local.x);
	phi = acos(local.y / sp->r);
	coords.x = (theta + M_PI) / (2 * M_PI);
	coords.y = phi / M_PI;
	coords.x = fmod(coords.x * hit.obj->tiles.x, 1.0);
	coords.y = fmod(coords.y * hit.obj->tiles.y, 1.0);
	return (coords);
}

t_vec2	plane_ratio(t_hit hit, t_pl *pl)
{
	t_vec3	local;
	t_vec2	coords;

	(void)pl;
	local = world_to_local(hit, hit.obj->coords);
	coords.x = local.x / hit.obj->tx->width;
	coords.y = local.z / hit.obj->tx->height;
	coords.x = fmod(coords.x * hit.obj->tiles.x, 1.0);
	coords.y = fmod(coords.y * hit.obj->tiles.y, 1.0);
	if (coords.x < 0)
		coords.x = 1 + coords.x;
	if (coords.y < 0)
		coords.y = 1 + coords.y;
	return (coords);
}

t_vec2	cylinder_ratio(t_hit hit, t_cy *cy)
{
	t_vec3	local;
	t_vec2	coords;
	double	tetha;

	local = world_to_local(hit, hit.obj->coords);
	tetha = atan2(local.z, local.x);
	coords.x = (tetha + M_PI) / (2 * M_PI);
	coords.y = 1.0 - (local.y + cy->h / 2.0) / cy->h;
	coords.x = fmod(coords.x * hit.obj->tiles.x, 1.0);
	coords.y = fmod(coords.y * hit.obj->tiles.y, 1.0);
	return (coords);
}

t_vec2	cone_ratio(t_hit hit, t_cn *cn)
{
	t_vec3	local;
	t_vec2	coords;
	double	theta;

	local = world_to_local(hit, hit.obj->coords);
	theta = atan2(local.z, local.x);
	coords.x = 1 - (theta + M_PI) / (2 * M_PI);
	coords.y = local.y / cn->h;
	coords.x = fmod(coords.x * hit.obj->tiles.x, 1.0);
	coords.y = fmod(coords.y * hit.obj->tiles.y, 1.0);
	return (coords);
}

t_vec2	rectangle_ratio(t_hit hit, t_rc *rc)
{
	t_vec3	local;
	t_vec2	coords;

	local = world_to_local(hit, hit.obj->coords);
	coords.x = (local.z + rc->width / 2.0) / rc->width;
	coords.y = (local.x + rc->height / 2.0) / rc->height;
	coords.x = fmod(coords.x * hit.obj->tiles.x, 1.0);
	coords.y = fmod(coords.y * hit.obj->tiles.y, 1.0);
	return (coords);
}
