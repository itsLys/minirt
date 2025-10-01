/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:34:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:34:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 world_to_local(t_hit hit, t_local_coords coords)
{
	t_vec3	local;
	t_vec3 rel;

	rel = vec3_subtract(hit.point, hit.obj->pos);
	// if (hit.obj->type == T_SP)
	// 	rel = vec3_norm(rel);
		// rel = hit.normal;
	local.x = vec3_dot(rel, coords.right);
	local.y = vec3_dot(rel, coords.up);
	local.z = vec3_dot(rel, coords.forward);
	return local;
}

t_rgb sample_tx_color(t_vec2 coords, t_texture *tx)
{
	int	x;
	int	y;

	x = coords.x * (tx->width - 1);
	y = coords.y * (tx->height - 1);

	return img_get_pixel(tx->img, x, y);
}

