/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:10:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:58:30 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		printf("\n");
		obj = obj->next;
	}
}

void	print_scene(t_data *data)
{
	t_scene	scene;

	scene = data->scene;
	printf("------------------------------\n");
	print_amb_light(scene.amb_light);
	print_light(scene.light);
	print_camera(scene.cam);
	printf("\n");
	print_objects(*scene.obj_list);
}

/*
   int	count_obj(t_obj *obj, t_obj_type type)
   {
   int	i;

   i = 0;
   while (obj)
   {
   if (obj->type == type )
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

*/

/*
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
   */

// WARN: fix norm of this
