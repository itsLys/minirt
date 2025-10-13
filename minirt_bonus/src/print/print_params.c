/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:49:02 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 11:01:52 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_pos(t_obj *obj)
{
	printf("%.2lf,%.2lf,%.2lf		",
		obj->pos.x,
		obj->pos.y,
		obj->pos.z);
}

void	print_color_props(t_obj *obj)
{
	printf("%d,%d,%d		",
		(int)(obj->color.r * 255.999),
		(int)(obj->color.g * 255.999),
		(int)(obj->color.b * 255.999));
	printf("%.2lf	", obj->ref);
	printf("%d	", obj->shine);
	if (obj->bmp)
		printf("%s	", obj->bmp->name);
	if (obj->tx)
		printf("%s	", obj->tx->name);
	if (obj->tx)
		printf("%d	%d", obj->tiles.x, obj->tiles.y);
}
