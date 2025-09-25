/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncategorized.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:45:50 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 15:45:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

t_rgb compute_avg(t_texture	*tx)
{
	t_rgb	avg;
	t_rgb	tmp;
	int		i;
	int		j;

	avg = int_to_rgb(0);
	i = 0;
	while (i < tx->width)
	{
		j = 0;
		while (j < tx->height)
		{
			tmp = img_get_pixel(tx->img, i, j++);
			avg = rgb_add(avg, tmp);
		}
		i++;
	}
	avg = rgb_scale(1.0 / (tx->width * tx->height), avg);
	return avg;
}
