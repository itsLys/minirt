/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:06:25 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/30 10:41:26 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_coords(int code, t_vec3 *point)
{
	if (code == XK_Up)
		point->z -= MOVE_STEP;
	else if (code == XK_Down)
		point->z += MOVE_STEP;
	else if (code == XK_Right)
		point->x += MOVE_STEP;
	else if (code == XK_Left)
		point->x -= MOVE_STEP;
	else if (code == XK_Page_Up)
		point->y += MOVE_STEP;
	else if (code == XK_Page_Down)
		point->y -= MOVE_STEP;
}

void	handle_obj_move(int code, t_data *data)
{
	if (data->selected.type == T_CAM)
		move_coords(code, &(data->scene.cam.pos));
	else if (data->selected.type == T_LIGHT)
		move_coords(code, &(data->scene.light.pos));
	else if (data->selected.type == T_OBJ)
		move_coords(code, &(data->selected.obj->pos));
}

