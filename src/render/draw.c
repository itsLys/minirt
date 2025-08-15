/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:53 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/14 16:00:59 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_ray	map_pixel(int x, int y, t_data *data)
// {
// 	
// }

void draw_image(t_data *data)
{
	int x;
	int y;
	int	color;
	// t_vec3 ray;

	x = 0;
	color = 0x0000FF00;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// ray = map_pixel(x, y, data);
			// color = compute_color(ray, data);
			// map_each_pixel
			// compute_color
			img_put_pixel(data, x, y, color);
			y++;
		}
		x++;
	}
}
//
