/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:01:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/12 09:37:08 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_obj	*obj;
	t_vec2	coords;

	hit.t = INFINITY;
	hit.hit = 0;
	hit.obj = NULL;
	obj = *(data->scene.obj_lst);
	record_hit(&obj, &hit, ray);
	if (hit.hit && (hit.obj->tx || hit.obj->bmp))
	{
		coords = compute_texture_ratio(hit);
		if (hit.obj->tx)
			hit.color = sample_tx_color(coords, hit.obj->tx);
		if (hit.obj->bmp)
			apply_bump_map(&hit, coords);
	}
	return (compute_color(ray, hit, data));
}
