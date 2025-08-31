/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:53:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 14:55:24 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rotate_obj(int code, t_vec3 *rot, t_cam cam)
{
	if (code == XK_d) // rotate around cam forw
		*rot = vec3_norm(rotate(*rot, cam.up, ROTATE_STEP));
	else if (code == XK_a)
		*rot = vec3_norm(rotate(*rot, cam.up, ROTATE_STEP * -1));
	else if (code == XK_w)
		*rot = vec3_norm(rotate(*rot, cam.right, ROTATE_STEP));
	else if (code == XK_s)
		*rot = vec3_norm(rotate(*rot, cam.right, ROTATE_STEP * -1));
	else if (code == XK_e)
		*rot = vec3_norm(rotate(*rot, cam.forward, ROTATE_STEP));
	else if (code == XK_q)
		*rot = vec3_norm(rotate(*rot, cam.forward, ROTATE_STEP * -1));
}

void	handle_obj_rotate(int code, t_obj *obj, t_cam cam)
{
	if (obj->type == T_CY)
		rotate_obj(code, &(((t_cy *)(obj->shape))->norm), cam);
	else if (obj->type == T_PL)
		rotate_obj(code, &(((t_pl *)(obj->shape))->norm), cam);
}
