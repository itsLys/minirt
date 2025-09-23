/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/23 12:48:30 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient_light(char *line, t_data *data)
{
	double		ratio;
	t_rgb		rgb;
	char		*tx_name;

	if (data->scene.amb.on == true)
		exit_error(ERR_AMB_LIGHT ERR_MULTI, data);
	ratio = get_double(&line, data);
	rgb = get_rgb(&line, data);
	tx_name = get_string(&line, data);
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	data->scene.amb.ratio = ratio;
	data->scene.amb.color = rgb;
	data->scene.amb.tx_name = tx_name;
	data->scene.amb.on = true;
	skip_trailing(line, data);
}

void	parse_camera(char *line, t_data *data)
{
	t_vec3	pos;
	t_vec3	norm;
	double	fov;

	if (data->scene.cam.on == true)
		exit_error(ERR_CAM ERR_MULTI, data);
	pos = get_vec3(&line, data);
	norm = vec3_norm(get_vec3(&line, data));
	fov = get_double(&line, data);
	if (fov < 0.0 || fov > 180.0)
		exit_error(ERR_CAM ERR_FOV, data);
	data->scene.cam.pos = pos;
	data->scene.cam.coords.forward = norm;
	data->scene.cam.fov = fov;
	data->scene.cam.on = true;
	setup_cam_coords(&(data->scene.cam));
	setup_viewport(&(data->scene.cam));
	skip_trailing(line, data);
}
