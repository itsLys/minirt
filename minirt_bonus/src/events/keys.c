/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/20 13:04:50 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_held_keys1(t_data *data)
{
	if (data->keys[XK_Up])
		handle_obj_move(XK_Up, data);
	else if (data->keys[XK_Down])
		handle_obj_move(XK_Down, data);
	if (data->keys[XK_Right])
		handle_obj_move(XK_Right, data);
	else if (data->keys[XK_Left])
		handle_obj_move(XK_Left, data);
	if (data->keys[XK_Page_Up])
		handle_obj_move(XK_Page_Up, data);
	else if (data->keys[XK_Page_Down])
		handle_obj_move(XK_Page_Down, data);
	if (data->keys[XK_w])
		handle_rotation(XK_w, data);
	else if (data->keys[XK_s])
		handle_rotation(XK_s, data);
	if (data->keys[XK_a])
		handle_rotation(XK_a, data);
	else if (data->keys[XK_d])
		handle_rotation(XK_d, data);
	if (data->keys[XK_q])
		handle_rotation(XK_q, data);
	else if (data->keys[XK_e])
		handle_rotation(XK_e, data);
}

void	handle_held_keys2(t_data *data)
{
	if (data->keys[XK_z])
		handle_strength(XK_z, data);
	else if (data->keys[XK_x])
		handle_strength(XK_x, data);
	if (data->keys[XK_equal])
		handle_props(XK_equal, data);
	else if (data->keys[XK_minus])
		handle_props(XK_minus, data);
	if (data->keys[XK_n])
		handle_props(XK_n, data);
	else if (data->keys[XK_m])
		handle_props(XK_m, data);
	if (data->keys[XK_g])
		handle_tiling(XK_g, data);
	else if (data->keys[XK_h])
		handle_tiling(XK_h, data);
	if (data->keys[XK_t])
		handle_tiling(XK_t, data);
	else if (data->keys[XK_y])
		handle_tiling(XK_y, data);
}
