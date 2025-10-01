/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:34:10 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:41:41 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	sample_bg_color(int x, int y, t_texture *tx)
{
	t_vec2	coords;

	coords.x = x / (WIDTH - 1.0);
	coords.y = y / (HEIGHT - 1.0);

	coords.x = fmod(coords.x * 1.0, 1.0);
	coords.y = fmod(coords.y * 1.0, 1.0);

	return sample_tx_color(coords,  tx);
}

t_rgb	sample_color(t_hit hit)
{
	if (hit.obj->type == T_SP)
		return sample_sp_color(hit, hit.obj->shape);
	else if (hit.obj->type == T_PL)
		return sample_pl_color(hit);
	else if (hit.obj->type == T_CY)
		return sample_cy_color(hit, hit.obj->shape);
	else
		return hit.obj->color;
	// else if (hit.obj->type == T_CN)
	// 	return sample_cn_color(hit, data); FIX: implement cone
}
