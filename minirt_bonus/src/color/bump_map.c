/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:17:58 by yel-guad          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define STRENGTH -5

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
	t_vec2	g;
	int		x;
	int		y;

	double (pr), (pl), (pd), (pu);
	x = (int)(crds.x * (tx->width - 1));
	y = (int)(crds.y * (tx->height - 1));
	pr = gray_ratio(img_get_pixel(tx->img, (x + 1) % tx->width, y));
	pl = gray_ratio(img_get_pixel(tx->img, (x -1 + tx->width) % tx->width, y));
	pd = gray_ratio(img_get_pixel(tx->img, x, (y + 1) % tx->height));
	pu = gray_ratio(img_get_pixel(tx->img, x, (y -1 + tx->height) % tx->height));
	g.x = (pr - pl);
	g.y = (pd - pu);
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
	compute_tangent_bitangent(*hit, &tangent, &bitangent);
	hit->normal = vec3_add(hit->normal, vec3_scale(STRENGTH * g.x, tangent));
	hit->normal = vec3_add(hit->normal, vec3_scale(STRENGTH * g.y, bitangent));
	hit->normal = vec3_norm(hit->normal);
}
