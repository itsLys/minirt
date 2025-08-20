/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/17 16:50:00 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// now we have the rays
// how do intergrate the math
// oc = o - c
// a = d.d
// b = (2 * vec3_dot(ray.dir * oc))
// c = (oc.oc - r.r)
// delta = b.b  -4ac
// t == (-b + (or -) sqrt(delta)) / 2a

// int	ray_hit(t_obj *obj, t_ray ray, t_data *data)
// {
// 	(void) data;
// 	t_vec3 oc;
// 	double r = ((t_sp *)obj->shape)->d / 2;
// 	double	t;
// 	double	a;
// 	double	b;
// 	double	c;
//
// 	oc = vec3_subtract(ray.orign, obj->pos);
// 	a = vec3_dot(ray.dir, ray.dir);
// 	b = 2 * vec3_dot(ray.dir, oc);
// 	c = vec3_dot(oc, oc) - r * r;
// 	t = (-b + sqrt(b * b - 4 * a * c)) / 2 * a;
// 	if (t >= 0)
// 		return obj->color.rgba;
// 	return 0;
// 	// BUG: when returning, the color could be black
// 	// 	figure out how to detect interesct in abstaction of color
// }

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	t;
	// double	delta;
}	t_quad ;

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

void	solve_quadratic(t_quad *quad)
{
	double	delta;

	delta = quad->b * quad->b - 4 * quad->a * quad->c;
	if (delta < 0)
		quad->t = -1.0;
	else
	{
		quad->t = (-quad->b - sqrt(delta)) / (2 * quad->a);
		if (quad->t < 0)
			quad->t = (-quad->b + sqrt(delta)) / (2 * quad->a);
	}
}

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
	hit.hit = quad.t > 0.0;
	hit.t = quad.t;
	return (hit);
}

t_hit	record_hit(t_obj *obj, t_ray ray, t_data *data)
{
	if (obj->type == T_SP)
		return intersect_sp(ray, obj, (t_sp *)(obj->shape), data);
	return ((t_hit) {false});
}

t_rgb	compute_color(t_hit hit, t_data *data)
{
	(void) data;
	t_rgb rgb;
	rgb.rgba = 0x00FF0000;
	if (hit.hit)
	{
		printf("t:	%lf\n", hit.t);
		rgb.rgba = 0x00000000;
	}
	return rgb;
}

t_rgb	trace_ray(t_ray ray, t_data *data)
{
	t_hit	hit;
	t_hit	tmp;
	t_obj	*obj;

	hit.t = INFINITY;
	hit.hit = 0;
	obj = *(data->scene.obj_list);
	while (obj)
	{
		tmp = record_hit(obj, ray, data);
		if (tmp.hit && tmp.t < hit.t)
			hit = tmp;
		obj = obj->next;
	}
	return compute_color(hit, data);
}

void draw_image(t_data *data)
{
	int		i;
	int		j;
	t_ray	ray;
	t_rgb	color;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ray = map_pixel(i, j, data->scene.cam);
			color = trace_ray(ray, data);
			img_put_pixel(data, i, j, color.rgba);
			j++;
		}
		i++;
	}
}
//
