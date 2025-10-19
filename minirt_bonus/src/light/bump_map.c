/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:17:58 by yel-guad          #+#    #+#             */
/*   Updated: 2025/10/19 11:12:01 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	gray_ratio(t_rgb color)
{
	return (0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
}

static void	compute_tan_bitan(t_hit hit, t_vec3 *t, t_vec3 *b, t_obj_type type)
{
	t_vec3	up;

	up = hit.obj->coords.up;
	if (type == T_CN)
		up = vec3_negate(up);
	*t = vec3_norm(vec3_cross(up, hit.normal));
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
	if (fabs(vec3_dot(hit->normal, hit->obj->coords.up)) > 0.9999
		&& hit->obj->type != T_PL && hit->obj->type != T_RC)
		return ;
	g = compute_height_gradient(tx, coords);
	if (hit->obj->type == T_PL || hit->obj->type == T_RC)
	{
		tangent = hit->obj->coords.forward;
		bitangent = hit->obj->coords.right;
	}
	else
		compute_tan_bitan(*hit, &tangent, &bitangent, hit->obj->type);
	hit->normal_bumped = vec3_add(hit->normal,
			vec3_scale(hit->obj->tx->strength * g.x, tangent));
	hit->normal_bumped = vec3_add(hit->normal_bumped,
			vec3_scale(hit->obj->tx->strength * g.y, bitangent));
	hit->normal_bumped = vec3_norm(hit->normal_bumped);
}
