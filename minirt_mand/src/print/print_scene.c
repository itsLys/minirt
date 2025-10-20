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

void	print_amb_light(t_light amb)
{
	printf("A	");
	printf("%.2lf				", amb.ratio);
	printf("%d,%d,%d			",
		(int)(amb.color.r * 255.999),
		(int)(amb.color.g * 255.999),
		(int)(amb.color.b * 255.999));
	printf("\n");
}

void	print_light(t_light light)
{
	printf("L	");
	print_vec3(light.pos);
	printf("%.2lf		", light.ratio);
	printf("\t\t");
	printf("%d,%d,%d		",
		(int)(light.color.r * 255.999),
		(int)(light.color.g * 255.999),
		(int)(light.color.b * 255.999));
	printf("\n");
}

void	print_camera(t_cam cam)
{
	printf("C	");
	printf("%.2lf,%.2lf,%.2lf		",
		cam.pos.x,
		cam.pos.y,
		cam.pos.z);
	printf("%.2lf,%.2lf,%.2lf		",
		cam.forward.x,
		cam.forward.y,
		cam.forward.z);
	printf("%.2lf", cam.fov);
	printf("\n");
}
