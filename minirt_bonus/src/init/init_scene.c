/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:10:37 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambient_light(char *line, t_data *data)
{
	double	ratio;
	t_rgb	rgb;

	if (data->scene.amb_light.on == true)
		exit_error(ERR_AMB_LIGHT ERR_MULTI, data);
	ratio = get_double(&line, data);
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	rgb = get_rgb(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	data->scene.amb_light.on = true;
	data->scene.amb_light.ratio = ratio;
	data->scene.amb_light.color = rgb;
}

// void	init_light(char *line, t_data *data)
// {
// 	double	ratio;
// 	t_vec3	pos;
// 	t_rgb	rgb;
//
// 	pos = get_vec3(&line, data);
// 	ratio = get_double(&line, data);
// 	rgb = get_rgb(&line, data);
// 	while (ft_isspace(*line))
// 		line++;
// 	if (*line != '\n' && *line != '\0')
// 		exit_error(ERR_EXTRA_PARAM, data);
// 	if (ratio < 0.0 || ratio > 1.0)
// 		exit_error(ERR_LIGHT ERR_RATIO, data);
// 	data->scene.light.on = true;
// 	data->scene.light.pos = pos;
// 	data->scene.light.ratio = ratio;
// 	data->scene.light.color = rgb;
// }

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
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	if (vec3_len(norm) != 1.0)
		exit_error(ERR_CAM ERR_NORM_VAL, data);
	if (fov < 0.0 || fov > 180.0)
		exit_error(ERR_CAM ERR_FOV, data);
	data->scene.cam.pos = pos;
	data->scene.cam.forward = norm;
	data->scene.cam.fov = fov;
	data->scene.cam.on = true;
}

int	init_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[i] == 'A' && ft_isspace(line[i + 1]))
		init_ambient_light(line + 1, data);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		init_camera(line + 1, data);
	else if (line[i] == 'l' && ft_isspace(line[i + 1]))
		init_light(line + 1, data);
	else if (!ft_strncmp(line, "pl", 2) && ft_isspace(line[i + 2]))
		init_plane(line + 2, data);
	else if (!ft_strncmp(line, "sp", 2) && ft_isspace(line[i + 2]))
		init_sphere(line + 2, data);
	else if (!ft_strncmp(line, "cy", 2) && ft_isspace(line[i + 2]))
		init_cylinder(line + 2, data);
	else if (!ft_strncmp(line, "cn", 2) && ft_isspace(line[i + 2]))
		init_cone(line + 2, data);
	else
		return (exit_error(ERR_PARAM, data), ERROR);
	return (SUCCESS);
}

#define SPLIT 2

void	init_workers(t_data *data)
{
	int i;

	i = 0;
	while (i < SPLIT * SPLIT)
	{
		data->workers[i].number = i;
		data->workers[i].data = data;
		set_worker_bounds(data->workers + i);
		i++;
	}
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->img.img_ptr = NULL;
	data->win = NULL;
	data->offsets = NULL;
	data->selected.light = NULL;
	data->scene.rays.dirs = NULL;
	data->scene.amb_light.on = false;
	data->scene.light_on = false;
	data->scene.cam.on = false;
	data->selected.type = T_CAM;
	data->workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	if (data->workers == NULL)
		exit_error(NULL, data);
	init_workers(data);
}
