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

int	ray_hit(t_obj *obj, t_ray ray, t_data *data)
{
	(void) data;
	// o = ray.origin;
	t_vec3 oc;
	double r = ((t_sp *)obj->shape)->d / 2;
	double	t;
	double	a;
	double	b;
	double	c;

	oc = vec3_subtract(ray.orign, obj->pos);
	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(ray.dir, oc);
	c = vec3_dot(oc, oc) - r * r;
	t = (-b + sqrt(b * b - 4 * a * c)) / 2 * a;
	if (t >= 0)
		return obj->color.rgba;
	return 0;

}

int	compute_color(t_ray ray, t_data *data)
{
	t_obj *obj = *(data->scene.obj_list);
	int color;
	while (obj)
	{
		if (obj->type == T_SP && (color = ray_hit(obj, ray, data)))
			return color;
		obj = obj->next;
	}
	return 0x0;
}

void draw_image(t_data *data)
{
	int i;
	int j;
	int	color;
	t_ray ray;

	i = 0;
	color = 0x0000FF00;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ray = map_pixel(i, j, data->scene.cam);
			color = compute_color(ray, data);
			img_put_pixel(data, i, j, color);
			j++;
		}
		i++;
	}
}
//
