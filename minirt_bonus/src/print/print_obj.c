/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:47:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:01:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sp(t_obj *obj)
{
	t_sp	*sp;

	printf("sp	");
	sp = (t_sp *)(obj->shape);
	print_vec3(obj->pos);
	printf("%.2lf		", sp->r * 2);
	printf("\t\t");
	print_color_props(obj);
}

void	print_pl(t_obj *obj)
{
	printf("pl	");
	print_vec3(obj->pos);
	print_vec3(obj->coords.up);
	print_color_props(obj);
}

void	print_cy(t_obj *obj)
{
	t_cy	*cy;

	printf("cy	");
	cy = (t_cy *)(obj->shape);
	print_vec3(obj->pos);
	print_vec3(obj->coords.up);
	printf("%.2lf		", cy->r * 2);
	printf("%.2lf		", cy->h);
	print_color_props(obj);
}

void	print_cn(t_obj *obj)
{
	t_cn	*cn;

	printf("cn	");
	cn = (t_cn *)(obj->shape);
	print_vec3(obj->pos);
	print_vec3(obj->coords.up);
	printf("%.2lf		", cn->angle * (360 / M_PI));
	printf("%.2lf		", cn->h);
	print_color_props(obj);
}

void	print_rc(t_obj *obj)
{
	t_rc	*rc;

	printf("rc	");
	rc = (t_rc *)(obj->shape);
	print_vec3(obj->pos);
	print_vec3(obj->coords.up);
	printf("%.2lf		", rc->width);
	printf("%.2lf		", rc->height);
	print_color_props(obj);
}
