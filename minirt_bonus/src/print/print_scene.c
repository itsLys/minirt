/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:48:10 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:02:05 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_amb_light(t_amb_light amb)
{
	printf("A	");
	printf("%.2lf				", amb.ratio);
	printf("%d, %d, %d			",
		(int)(amb.color.r * 255.999),
		(int)(amb.color.g * 255.999),
		(int)(amb.color.b * 255.999));
	if (amb.tx)
		printf("%s	", amb.tx->path);
	printf("\n");
}

void	print_camera(t_cam cam)
{
	printf("C	");
	printf("%.2lf, %.2lf, %.2lf		",
		cam.pos.x,
		cam.pos.y,
		cam.pos.z);
	printf("%.2lf, %.2lf, %.2lf		",
		cam.coords.forward.x,
		cam.coords.forward.y,
		cam.coords.forward.z);
	printf("%.2lf", cam.fov);
	printf("\n");
}
