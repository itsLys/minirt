/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:05:16 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 12:08:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdbool.h>

#define ERR_CAM "Camera: "
#define ERR_LIGHT "Light: "
#define ERR_RATIO "Ratio is not correct"
#define ERR_NORM_VAL "Normalized value is not correct\n"
#define ERR_FOV "Fov is not correct\n"

// WARN: need to check repitition of object that should be repeated
void	init_camera(char *line, t_data *data)
{
	t_coords	pos;
	t_coords	norm;
	int			fov;

	pos = get_vector(&line);
	norm = get_vector(&line);
	fov = get_integer(&line);
	if (norm.x + norm.y + norm.z != 1.0)
		exit_error(ERR_CAM ERR_NORM_VAL);
	if (fov < 0 || fov > 180)
		exit_error(ERR_CAM ERR_FOV);
	data->scene.cam.pos = pos;
	data->scene.cam.norm = norm;
	data->scene.cam.fov = fov;
}

void	init_source_light(char *line, t_data *data)
{
	// change to setup light, and set up amb and source with it
	t_obj			*obj;
	t_light_source	*source;
	t_coords		pos;
	double			ratio;
	t_rgb			rgba;

	pos = get_vector(&line);
	ratio = get_double(&line);
	rgba = get_rgba(&line);
	obj = malloc(sizeof(t_obj));
	source = malloc(sizeof(t_light_source));
	if (obj == NULL || source == NULL)
		exit_error(NULL);
	if (is_valid_ratio(ratio) == false)
		exit_error(ERR_LIGHT ERR_RATIO);
	if (rgba == ERROR)
		exit_error(ERR_LIGHT ERR_RGB);
	obj->type = OBJ_L;
	obj->pos = pos;
	obj->color = rgba;
	source->ratio = ratio;
	// obj_list_add ( source);
	// NOTE: CHANGE light_source to l
}
