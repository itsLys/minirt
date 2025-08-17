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

void draw_image(t_data *data)
{
	int i;
	int j;
	int	color;
	// t_vec3 ray;

	i = 0;
	color = 0x0000FF00;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			// ray = map_pixel(i, j, data->scene.cam);
			// color = compute_color(ray, data);
			img_put_pixel(data, i, j, color);
			j++;
		}
		i++;
	}
}
//
