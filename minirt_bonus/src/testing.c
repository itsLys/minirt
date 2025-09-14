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
	int	i;

	i = 0;
	while (obj /*  && printf("ptr:	%p\n", obj) */)
	{
		if (obj->type == type /*  && printf("type:	%d\n", obj->type) */)
			i++;
		obj = obj->next;
	}
	return (i);
}

void	print_scene_params(t_scene scene)
{
	t_obj	*obj;

	obj = *(scene.obj_list);
	printf("======== MINI RT SCENE CONFIGURATION ========\n");
	printf("Object count:	%d\n",
			count_obj(obj, T_SP) + count_obj(obj, T_PL) + count_obj(obj, T_CY));
}

void	print_amb_light(t_amb_light amb_light)
{
	printf("A	");
	printf("%.2lf		", amb_light.ratio);
	printf("%d, %d, %d",
			(int)(amb_light.color.r * 255.999),
			(int)(amb_light.color.g * 255.999),
			(int)(amb_light.color.b * 255.999));
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
			cam.forward.x,
			cam.forward.y,
			cam.forward.z);
	printf("%.2lf", cam.fov);
	printf("\n");
}

void	print_pos(t_obj *obj)
{
	printf("%.2lf, %.2lf, %.2lf		",
			obj->pos.x,
			obj->pos.y,
			obj->pos.z);
}

void	print_color_props(t_obj *obj)
{
	printf("%d, %d, %d		",
			(int)(obj->color.r * 255.999),
			(int)(obj->color.g * 255.999),
			(int)(obj->color.b * 255.999));
	printf("%.2lf	", obj->reflect);
	printf("%d	", obj->shine);
}

void	print_sp(t_obj *obj)
{
	t_sp	*sp;

	printf("sp	");
	sp = (t_sp *)(obj->shape);
	print_pos(obj);
	printf("%.2lf		", sp->r * 2);
	printf("\t\t");
	print_color_props(obj);
	printf("\n");
}

void	print_pl(t_obj *obj)
{
	t_pl	*pl;

	printf("pl	");
	pl = (t_pl *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			pl->norm.x,
			pl->norm.y,
			pl->norm.z);
	print_color_props(obj);
	printf("\n");
}

void	print_cy(t_obj *obj)
{
	t_cy	*cy;

	printf("cy	");
	cy = (t_cy *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			cy->norm.x,
			cy->norm.y,
			cy->norm.z);
	printf("%.2lf		", cy->r * 2);
	printf("%.2lf		", cy->h);
	print_color_props(obj);
	printf("\n");
}

void	print_cn(t_obj *obj)
{
	t_cn	*cn;

	printf("cn	");
	cn = (t_cn *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			cn->norm.x,
			cn->norm.y,
			cn->norm.z);
	printf("%.2lf		", cn->angle);
	printf("%.2lf		", cn->h);
	print_color_props(obj);
	printf("\n");
}

void	print_light(t_obj *obj)
{
	t_light	*light;

	printf("l	");
	light = (t_light *)(obj->shape);
	print_pos(obj);
	printf("%.2lf		", light->ratio);
	printf("\t\t");
	printf("%d, %d, %d		",
			(int)(obj->color.r * 255.999),
			(int)(obj->color.g * 255.999),
			(int)(obj->color.b * 255.999));
	printf("\n");
}

void	print_objects(t_obj *obj)
{
	while (obj)
	{
		if (obj->type == T_PL)
			print_pl(obj);
		else if (obj->type == T_CY)
			print_cy(obj);
		else if (obj->type == T_SP)
			print_sp(obj);
		else if (obj->type == T_LS)
			print_light(obj);
		obj = obj->next;
	}
}

void	print_scene(t_data *data)
{
	t_scene	scene;

	scene = data->scene;
	print_scene_params(scene);
	print_amb_light(scene.amb_light);
	print_camera(scene.cam);
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
			ray.dir.z);
}

void	print_vec3(t_vec3 vec)
{
	printf("vec:		(%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
}

void	print_obj_type(t_obj *obj)
{
	if (obj == NULL)
	{
		printf("DOESN'T EXIST\n");
		return;
	}
	if (obj->type == T_SP)
		printf("SPHERE\n");
	else if (obj->type == T_PL)
		printf("PLANE\n");
	else if (obj->type == T_CY)
		printf("CYLINDER\n");
	else if (obj->type == T_CN)
		printf("CONE\n");
	else if (obj->type == T_LS)
		printf("LIGHT\n");
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
