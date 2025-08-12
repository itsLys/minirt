/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 16:06:48 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_scene_params(t_scene scene)
{
	double	light_ratio	= scene.amb_light.ratio;
	uint8_t r			= scene.amb_light.color.r;
	uint8_t g			= scene.amb_light.color.g;
	uint8_t b			= scene.amb_light.color.b;
	double	cam_x		= scene.cam.pos.x;
	double	cam_y		= scene.cam.pos.y;
	double	cam_z		= scene.cam.pos.z;
	int		light_count	= count_obj(scene.objs, T_LS);
	int		obj_count	= count_obj(scene.objs, T_CY) + count_objs(scene.objs, T_PL) + count_objs(scene.objs, T_SP);
	printf("======== MINI RT SCENE ========\n");
	printf("Ambient Light:	%lf | Color:	(%d, %d, %d)\n", light_ratio, r, g, b);
	printf("Camera:			(%lf, %lf, %lf)\n", cam_x, cam_y, cam_z);
	printf("Light Count:	%d\n", light_count);
	printf("Object Count:	%d\n", obj_count);
	printf("--------------------------------\n");
}

void	print_scene(t_data *data)
{
	t_scene scene = data->scene;
	print_scene_params(scene);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return print_error("Wrong args\n"), FAILIURE;
	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	print_scene(&data);
	printf("Hello\n");
}
