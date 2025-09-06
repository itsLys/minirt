/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_offsets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:33:42 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:34:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_offsets(t_vec2 **offsets, t_data *data)
{
	int i;
	int j;
	double px;
	double py;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			px = (i + 0.5) / WIDTH;
			py = (j + 0.5) / HEIGHT;
			px = (px - 0.5) * data->scene.cam.viewport_w;
			py = (0.5 - py) * data->scene.cam.viewport_h;
			(*offsets)[j * WIDTH + i].x = px;
			(*offsets)[j * WIDTH + i].y = py;
			j++;
		}
		i++;
	}
}

void	init_offsets(t_vec2	**offsets, t_data *data)
{
	*offsets = malloc(sizeof(t_vec2) * WIDTH * HEIGHT);
	if (*offsets == NULL)
		clean_exit(data, FAILIURE);
	set_offsets(offsets, data);
}
