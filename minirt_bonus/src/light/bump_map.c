/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:17:58 by yel-guad          #+#    #+#             */
/*   Updated: 2025/10/14 16:08:58 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define STRENGTH -3

static double	gray_ratio(t_rgb color)
{
	return (0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
}

static void	compute_tangent_bitangent(t_hit hit, t_vec3 *t, t_vec3 *b)
{
	*t = vec3_norm(vec3_cross(hit.obj->coords.up, hit.normal));
	*b = vec3_cross(*t, hit.normal);
}

static t_vec2	compute_height_gradient(t_texture *tx, t_vec2 crds)
{
	t_vec2			g;
	int				x;
	int				y;
	t_pixel_neigh	p;

	x = (int)(crds.x * (tx->width - 1));
	y = (int)(crds.y * (tx->height - 1));
	p.r = gray_ratio(img_get_pixel(tx->img, (x + 1) % tx->width, y));
	p.l = gray_ratio(img_get_pixel(tx->img,
				(x - 1 + tx->width) % tx->width, y));
	p.d = gray_ratio(img_get_pixel(tx->img, x, (y + 1) % tx->height));
	p.u = gray_ratio(img_get_pixel(tx->img, x,
				(y - 1 + tx->height) % tx->height));
	g.x = (p.r - p.l);
	g.y = (p.d - p.u);
	return (g);
}

void	apply_bump_map(t_hit *hit, t_vec2 coords)
{
	t_texture	*tx;
	t_vec2		g;
	t_vec3		tangent;
	t_vec3		bitangent;

	tx = hit->obj->bmp;
	g = compute_height_gradient(tx, coords);
	if (hit->obj->type == T_PL || hit->obj->type == T_RC)
	{
		tangent = hit->obj->coords.forward;	
		bitangent = hit->obj->coords.right;	
	}
	else
		compute_tangent_bitangent(*hit, &tangent, &bitangent);
	hit->normal_bumped = vec3_add(hit->normal, vec3_scale(STRENGTH * g.x, tangent));
	hit->normal_bumped = vec3_add(hit->normal_bumped, vec3_scale(STRENGTH * g.y, bitangent));
	hit->normal_bumped = vec3_norm(hit->normal_bumped);
}
