/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:04:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/20 17:05:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
 * R(t) = o + t.d
 * |P - c|^2 = r^2
 * (R(t) - c)^2 = r^2
 * (o + t.d - c)^2 = r^2
 * (oc + t.d)^2 = r^2
 * oc^2 + 2.t.d.oc + (t.d)^2 - r^2 = 0
 * (t.d)^2 + t.2.d.oc + oc^2 - r^2 = 0
 * ax^2 + bx + c = 0
 * x = (-b +- sqrt(delta)) / 2a
 * delta = b^2 - 4ac
 * 
*/
/* ray.dir ^ 2 = 1; */
t_hit	intersect_sp(t_ray ray, t_obj *obj, t_sp *sp, t_data *data)
{
	(void) data;
	t_quad	quad;
	t_hit	hit;
	t_vec3	oc;
	// NOTE: replace sp.d / 2 with sp.r that is put directly in when parsing
	double	r = sp->d / 2;
	// END NOTE

	oc = vec3_subtract(ray.orign, obj->pos);
	quad.a = 1;
	quad.b = 2 * vec3_dot(ray.dir, oc);
	quad.c = vec3_dot(oc, oc) - r * r;
	solve_quadratic(&quad);
	hit.hit = quad.t1 > 0.0 || quad.t2 > 0.0;
	hit.t = quad.t1;
	if (hit.t < 0.0)
		hit.t = quad.t2;
	return (hit);
}

void	check_cy_height(t_hit *hit, t_ray ray, t_obj *obj, t_cy *cy)
{
	t_vec3	check_height;
	double	q;

	check_height = vec3_scale(hit->t, ray.dir);
	check_height = vec3_add(check_height, ray.orign);
	check_height = vec3_subtract(check_height, obj->pos);
	q = vec3_dot(check_height, cy->norm);
	if (q >= -cy->h/2.0 && q <= cy->h/2.0)
		return ;
	hit->hit = false;
}

// NOTE: need to understand the equation and write it here
t_hit    intersect_cy(t_ray ray, t_obj *obj, t_cy *cy, t_data *data)
{
	(void) data;
	t_vec3	oc;
	t_hit	hit;
	t_quad	quad;
	// NOTE: replace sp.d / 2 with sp.r that is put directly in when parsing
	double    r = cy->d / 2;
	//END NOTE
	hit.hit = false;
	oc = vec3_subtract(ray.orign, obj->pos);
	quad.a = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy->norm), 2); //  x*x faster than pow(x, 2)
	quad.b = 2 * (vec3_dot(oc, ray.dir) - vec3_dot(oc, cy->norm) * vec3_dot(ray.dir, cy->norm));
	quad.c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy->norm), 2) - r * r; // Same 'x*x faster than pow(x, 2)'
	solve_quadratic(&quad);
	hit.hit = (quad.t1 > 0.0);
	hit.t = quad.t1;
	if (quad.t1 > 0.0)
		check_cy_height(&hit, ray, obj, cy);
	if (hit.hit == false && quad.t2 > 0.0)
	{
		hit.hit = quad.t2 > 0.0;
		hit.t = quad.t2;
		hit.hit = true;
		check_cy_height(&hit, ray, obj, cy);
	}
	return (hit);
}

t_hit    intersect_pl(t_ray ray, t_obj *obj, t_pl *pl, t_data *data)
{
	(void) data;
	double	a;
	double	b;
	double	t;
	t_hit	hit;

	hit.hit = true;
	a = vec3_dot(vec3_subtract(obj->pos, ray.orign), pl->norm);
	b = vec3_dot(ray.dir, pl->norm);
	if (b < 0.000001 && b > -0.000001) //   lma9am almost 0 take it as ZERO ->forbiden // check this again
		hit.hit = false;
	t = a / b;
	if (t < 0.00001)  //       find the best value to compare t if close to 0 ...
		hit.hit = false;
	hit.t = t;
	return (hit);
}


