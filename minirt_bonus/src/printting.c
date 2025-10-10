/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:10:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 11:36:48 by ihajji           ###   ########.fr       */
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

	obj = *(scene.obj_lst);
	printf("======== MINI RT SCENE CONFIGURATION ========\n");
	printf("Object count:	%d\n",
			count_obj(obj, T_SP) + count_obj(obj, T_PL) + count_obj(obj, T_CY));
}

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
	printf("%.2lf	", obj->ref);
	printf("%d	", obj->shine);
	if (obj->bmp)
		printf("%s	", obj->bmp->name);
	if (obj->tx)
		printf("%s	", obj->tx->name);
	if (obj->tx)
		printf("%d	%d\n", obj->tiles.x, obj->tiles.y);
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
}

void	print_pl(t_obj *obj)
{
	// t_pl	*pl;

	printf("pl	");
	// pl = (t_pl *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			obj->coords.up.x,
			obj->coords.up.y,
			obj->coords.up.z);
	print_color_props(obj);
}

void	print_cy(t_obj *obj)
{
	t_cy	*cy;

	printf("cy	");
	cy = (t_cy *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			obj->coords.up.x,
			obj->coords.up.y,
			obj->coords.up.z);
	printf("%.2lf		", cy->r * 2);
	printf("%.2lf		", cy->h);
	print_color_props(obj);
}

void	print_cn(t_obj *obj)
{
	t_cn	*cn;

	printf("cn	");
	cn = (t_cn *)(obj->shape);
	print_pos(obj);
	printf("%.2lf, %.2lf, %.2lf		",
			obj->coords.up.x,
			obj->coords.up.y,
			obj->coords.up.z);
	printf("%.2lf		", cn->angle * (180 / M_PI));
	printf("%.2lf		", cn->h);
	print_color_props(obj);
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
		else if (obj->type == T_CN)
			print_cn(obj);
		obj = obj->next;
	}
}

void	print_texture_type(t_texture *lst)
{
	if (lst->type == TX_COLOR)
		printf("color");
	else if (lst->type == TX_BUMP)
		printf("bump");
	else if (lst->type == TX_PATT)
		printf("patt");
}

void	print_textures(t_texture *lst)
{
	while (lst)
	{
		printf("t	");
		printf("%s			", lst->name);
		print_texture_type(lst);
		if (lst->type == TX_PATT)
		{
			printf("%d, %d, %d		",
					(int)(lst->c1.r * 255.999),
					(int)(lst->c1.g * 255.999),
					(int)(lst->c1.b * 255.999));
			printf("%d, %d, %d		",
					(int)(lst->c2.r * 255.999),
					(int)(lst->c2.g * 255.999),
					(int)(lst->c2.b * 255.999));
		}
		printf("	%s			", lst->path);
		printf("\n");
		lst = lst->next;
	}
	// FIX: add relative path string for printing, free at exit,, also COLOR PRINTING
}

void	print_scene(t_data *data)
{
	t_scene	scene;

	scene = data->scene;
	print_scene_params(scene);
	printf("\n");
	print_amb_light(scene.amb);
	print_camera(scene.cam);
	printf("\n");
	print_textures(*scene.tx_lst);
	printf("\n");
	print_objects(*scene.obj_lst);
}

void	print_ray(int x, int y, t_ray ray)
{
	printf("-----\n");
	printf("pixel:	x:	%d, y:	%d\n", x, y);
	printf("origin:	[%.2lf, %.2lf, %.2lf] - direction: [%.2lf, %.2lf, %.2lf]\n",
			ray.orig.x,
			ray.orig.y,
			ray.orig.z,
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
		return ;
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

// WARN: fix norm of this
