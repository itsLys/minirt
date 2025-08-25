/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:10:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/24 11:53:21 by ihajji           ###   ########.fr       */
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

void	print_scene_params(t_scene scene)
{
	t_obj	*obj = *(scene.obj_list);
	printf("======== MINI RT SCENE PARAMETERS ========\n");
	printf("Object count:	%d\n",
			count_obj(obj, T_SP)
			+ count_obj(obj, T_PL)
			+ count_obj(obj, T_CY));
}

void	print_amb_light(t_light amb_light)
{
	printf("------------------------------------------\n");
	printf("[Ambient Light]\n");
	printf("Color:	(%d, %d, %d)\n",
			(int)(amb_light.color.r * 255.999),
			(int)(amb_light.color.g * 255.999),
			(int)(amb_light.color.b * 255.999));
	printf("Ratio:	%.2lf\n", amb_light.ratio);
	printf("\n");
}

void	print_camera(t_cam cam)
{
	printf("------------------------------------------\n");
	printf("[Camera]\n");
	printf("Position:	(%.2lf, %.2lf, %.2lf)\n",
			cam.pos.x,
			cam.pos.y,
			cam.pos.z);
	printf("Orientation:	(%.2lf, %.2lf, %.2lf)\n",
			cam.forward.x,
			cam.forward.y,
			cam.forward.z);
	printf("FOV:		%.2lf°\n", cam.fov);
	printf("\n");
}

void	print_light(t_light light)
{
	printf("------------------------------------------\n");
	printf("[Light]\n");
	printf("Color:	(%d, %d, %d)\n",
			(int)(light.color.r * 255.999),
			(int)(light.color.g * 255.999),
			(int)(light.color.b * 255.999));
	printf("Ratio:	%.2lf\n", light.ratio);
	printf("\n");
}

void	print_obj_common(t_obj	*obj)
{
	printf("Position:	(%.2lf, %.2lf, %.2lf)\n",
			obj->pos.x,
			obj->pos.y,
			obj->pos.z);
	printf("Color:	(%d, %d, %d)\n",
			(int)(obj->color.r * 255.999),
			(int)(obj->color.g * 255.999),
			(int)(obj->color.b * 255.999));
}

void	print_sp(t_obj	*obj)
{
	printf("------------------------------------------\n");
	printf("[Spheres]\n");
	int i = 1;
	while (obj)
	{
		if (obj->type == T_SP)
		{
			t_sp *sp = (t_sp *)(obj->shape);
			printf("Number:			%d\n", i++);
			print_obj_common(obj);
			printf("Diameter:		%.2lf\n", sp->d);
			printf("\n");
		}
		obj = obj->next;
	}
}

void	print_pl(t_obj	*obj)
{
	printf("------------------------------------------\n");
	printf("[Planes]\n");
	int i = 1;
	while (obj)
	{
		if (obj->type == T_PL)
		{
			t_pl *pl = (t_pl *)(obj->shape);
			printf("Number:			%d\n", i++);
			print_obj_common(obj);
			printf("Normalized:	(%.2lf, %.2lf, %.2lf)\n",
					pl->norm.x,
					pl->norm.y,
					pl->norm.z);
			printf("\n");
		}
		obj = obj->next;
	}
}

void	print_cy(t_obj	*obj)
{
	printf("------------------------------------------\n");
	printf("[Cylinders]\n");
	int i = 1;
	while (obj)
	{
		if (obj->type == T_CY)
		{
			t_cy *cy = (t_cy *)(obj->shape);
			printf("Number:			%d\n", i++);
			print_obj_common(obj);
			printf("Diameter:		%.2lf\n", cy->d);
			printf("Height:			%.2lf\n", cy->h);
			printf("Normalized:	(%.2lf, %.2lf, %.2lf)\n",
					cy->norm.x,
					cy->norm.y,
					cy->norm.z);
			printf("\n");
		}
		obj = obj->next;
	}
}

void print_objects(t_obj *obj)
{
	print_sp(obj);
	print_pl(obj);
	print_cy(obj);
}

void	print_scene(t_data *data)
{
	t_scene scene = data->scene;
	print_scene_params(scene);
	print_amb_light(scene.amb_light);
	print_camera(scene.cam);
	print_light(scene.light);
	print_objects(*scene.obj_list);
}

void	print_ray(int x, int y, t_ray ray)
{
	printf("-----\n");
	printf("pixel:	x:	%d, y:	%d\n", x, y);
	printf("origin:	[%.2lf, %.2lf, %.2lf] - direction: [%.2lf, %.2lf, %.2lf]\n",
			ray.orign.x,
			ray.orign.y,
			ray.orign.z,
			ray.dir.x,
			ray.dir.y,
			ray.dir.z
		  );
}

void	print_vec3(t_vec3 vec)
{
	printf("vec:		(%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
}

// ======== MINI RT SCENE PARAMETERS ========
// Object Count:   6
// ------------------------------------------
//
// ------------------------------------------
// [Light]
// Ratio:          0.10
// Position:       (0.00, 0.00, 0.00)
// Color:          (255, 255, 255)
// ------------------------------------------
// [Camera]
// Position:       (-5.00, 0.00, 30.00)
// Orientation:        (0.00, 0.00, -1.00)
// Field of view:      70°
//
// ------------------------------------------
// [Light]
// Ratio:          0.70
// Position:       (0.00, 10.00, 5.00)
// Color:          (255, 255, 255)
// ------------------------------------------
// [Spheres]
// Number:         1
// Position:       (4.00, 0.00, -20.00)
// Diameter:       18.00
// Color:          (255, 0, 255)
//
// Number:         2
// Position:       (4.00, 0.00, 20.00)
// Diameter:       8.00
// Color:          (255, 255, 0)
//
// Number:         3
// Position:       (4.00, 0.00, 0.00)
// Diameter:       1.00
// Color:          (0, 255, 0)
//
// Number:         4
// Position:       (0.00, 0.00, 0.00)
// Diameter:       3.00
// Color:          (0, 255, 0)
//
// ------------------------------------------
// [Cylinders]
// Number:         1
// Position:       (0.00, 0.00, 0.00)
// Normalized:     (1.00, 0.00, 0.00)
// Diameter:       7.00
// Height:         10.00
// Color:          (0, 255, 0)
//
// ------------------------------------------
// [Planes]
// Number:         1
// Position:       (0.00, -10.00, 0.00)
// Normalized:     (0.00, 1.00, 0.00)
// Color:          (50, 200, 200)
