/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 11:38:37 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

// FIX: this is not part of the texture list, 
// must be freeed seperately
static void	init_amb_tx(char **line, t_data *data)
{
	t_texture	*tx;
	char		*path;

	path = get_string(line, data);
	if (path == NULL)
		return ;
	tx = malloc(sizeof(t_texture));
	if (tx == NULL)
		return (free(path), exit_error(NULL, data));
	tx->path = path;
	tx->type = TX_COLOR;
	get_image(tx, data);
	data->scene.amb.tx = tx;
}

void	parse_ambient_light(char *line, t_data *data)
{
	double	ratio;
	t_rgb	rgb;

	if (data->scene.amb.on == true)
		exit_error(ERR_AMB_LIGHT ERR_MULTI, data);
	ratio = get_double_parameter(&line, data);
	rgb = get_rgb(&line, data);
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	data->scene.amb.ratio = ratio;
	data->scene.amb.color = rgb;
	data->scene.amb.on = true;
	init_amb_tx(&line, data);
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
	fov = get_double_parameter(&line, data);
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
