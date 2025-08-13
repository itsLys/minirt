/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:10:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/13 12:05:11 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_obj(t_obj *obj, t_obj_type type)
{
	int i = 0;
	while (obj/*  && printf("ptr:	%p\n", obj) */)
	{
		if (obj->type == type/*  && printf("type:	%d\n", obj->type) */)
			i++;
		obj = obj->next;
	}
	return i;
}

void print_scene_params(t_scene scene)
{
	int		light_count	= count_obj(*(scene.obj_list), T_LS);
	int		obj_count	= count_obj(*(scene.obj_list), T_CY) + count_obj(*(scene.obj_list), T_PL) + count_obj(*(scene.obj_list), T_SP);
	printf("======== MINI RT SCENE PARAMETERS ========\n");
	printf("Light Count:	%d\n", light_count);
	printf("Object Count:	%d\n", obj_count);
	printf("------------------------------------------\n");
	printf("\n");
}

void print_ambient_light(t_scene scene)
{
	double	light_ratio	= scene.amb_light.ratio;
	uint8_t r			= scene.amb_light.color.r;
	uint8_t g			= scene.amb_light.color.g;
	uint8_t b			= scene.amb_light.color.b;
	printf("------------------------------------------\n");
	printf("[Ambient Light]\n");
	printf("Ratio:			%.2lf\n", light_ratio);
	printf("Color:			(%d, %d, %d)\n", r, g, b);
	printf("\n");
}

void print_camera(t_scene scene)
{
	double	cam_x		= scene.cam.pos.x;
	double	cam_y		= scene.cam.pos.y;
	double	cam_z		= scene.cam.pos.z;
	double	cam_nx		= scene.cam.norm.x;
	double	cam_ny		= scene.cam.norm.y;
	double	cam_nz		= scene.cam.norm.z;
	int		fov			= scene.cam.fov;
	printf("------------------------------------------\n");
	printf("[Camera]\n");
	printf("Position:		(%.2lf, %.2lf, %.2lf)\n", cam_x, cam_y, cam_z);
	printf("Orientation:		(%.2lf, %.2lf, %.2lf)\n", cam_nx, cam_ny, cam_nz);
	printf("Field of view:		%d°\n", fov);
	printf("\n");
}

void	print_lights(t_scene scene)
{
	t_obj	*obj		= *(scene.obj_list);

	printf("------------------------------------------\n");
	printf("[Lights]\n");
	int i = 0;
	while (obj)
	{
		double	x			= obj->pos.x;
		double	y			= obj->pos.y;
		double	z			= obj->pos.z;
		uint8_t r			= obj->color.r;
		uint8_t g			= obj->color.g;
		uint8_t b			= obj->color.b;
		if (obj->type == T_LS)
		{
			t_light_src	*shape	= (t_light_src *) obj->shape;
			printf("Number:			%d\n", ++i);
			printf("Ratio:			%.2lf\n", shape->ratio);
			printf("Position:		(%.2lf, %.2lf, %.2lf)\n", x, y, z);
			printf("Color:			(%d, %d, %d)\n", r, g, b);
			printf("\n");
		}
		obj = obj->next;
	}
}

void	print_sp(t_scene scene)
{
	t_obj	*obj		= *(scene.obj_list);

	printf("------------------------------------------\n");
	printf("[Spheres]\n");
	int i = 0;
	while (obj)
	{
		double	x			= obj->pos.x;
		double	y			= obj->pos.y;
		double	z			= obj->pos.z;
		uint8_t r			= obj->color.r;
		uint8_t g			= obj->color.g;
		uint8_t b			= obj->color.b;
		if (obj->type == T_SP)
		{
			t_sp	*shape	= (t_sp *) obj->shape;
			printf("Number:			%d\n", ++i);
			printf("Position:		(%.2lf, %.2lf, %.2lf)\n", x, y, z);
			printf("Diameter:		%.2lf\n", shape->d);
			printf("Color:			(%d, %d, %d)\n", r, g, b);
			printf("\n");
		}
		obj = obj->next;
	}
}

void	print_cy(t_scene scene)
{
	t_obj	*obj		= *(scene.obj_list);

	printf("------------------------------------------\n");
	printf("[Cylinders]\n");
	int i = 0;
	while (obj)
	{
		double	x			= obj->pos.x;
		double	y			= obj->pos.y;
		double	z			= obj->pos.z;
		uint8_t r			= obj->color.r;
		uint8_t g			= obj->color.g;
		uint8_t b			= obj->color.b;
		if (obj->type == T_CY)
		{
			t_cy	*shape	= (t_cy *) obj->shape;
			double nx		= shape->norm.x;
			double ny		= shape->norm.y;
			double nz		= shape->norm.z;
			printf("Number:			%d\n", ++i);
			printf("Position:		(%.2lf, %.2lf, %.2lf)\n", x, y, z);
			printf("Normalized:		(%.2lf, %.2lf, %.2lf)\n", nx, ny, nz);
			printf("Diameter:		%.2lf\n", shape->d);
			printf("Height:			%.2lf\n", shape->h);
			printf("Color:			(%d, %d, %d)\n", r, g, b);
			printf("\n");
		}
		obj = obj->next;
	}
}


void	print_pl(t_scene scene)
{
	t_obj	*obj		= *(scene.obj_list);

	printf("------------------------------------------\n");
	printf("[Planes]\n");
	int i = 0;
	while (obj)
	{
		double	x			= obj->pos.x;
		double	y			= obj->pos.y;
		double	z			= obj->pos.z;
		uint8_t r			= obj->color.r;
		uint8_t g			= obj->color.g;
		uint8_t b			= obj->color.b;
		if (obj->type == T_PL)
		{
			t_pl	*shape	= (t_pl *) obj->shape;
			double nx		= shape->norm.x;
			double ny		= shape->norm.y;
			double nz		= shape->norm.z;
			printf("Number:			%d\n", ++i);
			printf("Position:		(%.2lf, %.2lf, %.2lf)\n", x, y, z);
			printf("Normalized:		(%.2lf, %.2lf, %.2lf)\n", nx, ny, nz);
			printf("Color:			(%d, %d, %d)\n", r, g, b);
			printf("\n");
		}
		obj = obj->next;
	}
}

void print_objects(t_scene scene)
{
	print_lights(scene);
	print_sp(scene);
	print_cy(scene);
	print_pl(scene);
}

void	print_scene(t_data *data)
{
	t_scene scene = data->scene;
	print_scene_params(scene);
	print_ambient_light(scene);
	print_camera(scene);
	print_objects(scene);
}
