/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 12:17:37 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambient_light(char *line, t_data *data)
{
	double		ratio;
	t_rgb		rgb;
	char		*tx_name;

	if (data->scene.amb.on == true)
		exit_error(ERR_AMB_LIGHT ERR_MULTI, data);
	ratio = get_double(&line, data);
	rgb = get_rgb(&line, data);
	tx_name = get_string(&line, data); // FIX: free at exit
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	data->scene.amb.ratio = ratio;
	data->scene.amb.color = rgb;
	data->scene.amb.tx_name = tx_name;
	data->scene.amb.on = true;
	skip_trailing(line, data);
}

void	init_pattern(char *line, t_data *data)
{
	t_pattern	*patt;

	patt = malloc(sizeof(t_pattern));
	if (patt == NULL)
		return exit_error(NULL, data);
	pattern_add(patt, data->scene.patt_lst);
	patt->name = get_string(&line, data);
	patt->c1 = get_rgb(&line, data);
	patt->c2 = get_rgb(&line, data);
	skip_trailing(line, data);
	// FIX: need to validate duplicates
}

void	init_texture(char *line, t_data *data)
{
	t_texture	*tx;

	tx = malloc(sizeof(t_texture));
	if (tx == NULL)
		return (exit_error(NULL, data));
	texture_add(tx, data->scene.tx_lst);
	tx->name = get_string(&line, data);
	tx->type = get_type(&line, data);
	get_texture(tx, &line, data);
	skip_trailing(line, data);
	// FIX: need to validate duplicates
}

void	init_camera(char *line, t_data *data)
{
	t_vec3	pos;
	t_vec3	norm;
	double	fov;

	if (data->scene.cam.on == true)
		exit_error(ERR_CAM ERR_MULTI, data);
	pos = get_vec3(&line, data);
	norm = get_vec3(&line, data);
	fov = get_double(&line, data);
	if (!is_close(vec3_len(norm), 1.0))
		exit_error(ERR_CAM ERR_NORM_VAL, data);
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
