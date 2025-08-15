/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/13 09:29:45 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

# define ERR_EXTRA_PARAM "Extra parameter!"

void	init_ambient_light(char *line, t_data *data)
{
	double	ratio;
	t_rgb	rgba;

	ratio = get_double(&line, data);;
	if  (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT, data);
	rgba = get_rgba(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	if ((int) rgba.a == ERROR)
		exit_error(ERR_RGB, data);
	data->scene.amb_light.ratio = ratio;
	data->scene.amb_light.color = rgba;
}

void	init_camera(char *line, t_data *data)
{
	t_vec3	pos;
	t_vec3	norm;
	int			fov;

	pos = get_vec3(&line, data);
	norm = get_vec3(&line, data);
	fov = get_integer(&line, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	if (vec3_len(norm) != 1.0)
		exit_error(ERR_CAM ERR_NORM_VAL, data);
	if (fov < 0 || fov > 180)
		exit_error(ERR_CAM ERR_FOV, data);
	data->scene.cam.pos = pos;
	data->scene.cam.norm = norm;
	data->scene.cam.fov = fov;
}

int init_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	// printf("init config: line	|%s|\n", line);
	if (line[i] == 'A' && ft_isspace(line[i + 1]))
		init_ambient_light(line + 1, data);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		init_camera(line + 1, data);
	else if (line[i] == 'L' && ft_isspace(line[i + 1]))
		init_source_light(line + 1, data);
	else if (!ft_strncmp(line, "pl", 2) && ft_isspace(line[i + 2]))
		init_plane(line + 2, data);
	else if (!ft_strncmp(line, "sp", 2) && ft_isspace(line[i + 2]))
		init_sphere(line + 2, data);
	else if (!ft_strncmp(line, "cy", 2) && ft_isspace(line[i + 2]))
		init_cylinder(line + 2, data);
	else
		return exit_error(ERR_PARAM, data), ERROR;
	return SUCCESS;
}

int	process_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (init_config(line + i, data) == ERROR)
		return ERROR;
	return SUCCESS;
}
