/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/12 16:11:37 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ambient_light(char *line, t_data *data)
{
	double	ratio;
	t_rgb	rgba;

	ratio = get_double(&line);;
	if  (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT);
	rgba = get_rgba(&line);
	if ((int) rgba.a == ERROR)
		exit_error(ERR_RGB);
	data->scene.amb_light.ratio = ratio;
	data->scene.amb_light.color = rgba;
}

void	init_camera(char *line, t_data *data)
{
	t_coords	pos;
	t_coords	norm;
	int			fov;

	pos = get_vec3(&line);
	norm = get_vec3(&line);
	fov = get_integer(&line);
	if (vec3_len(norm) != 1.0)
		exit_error(ERR_CAM ERR_NORM_VAL);
	if (fov < 0 || fov > 180)
		exit_error(ERR_CAM ERR_FOV);
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
		return exit_error(ERR_PARAM), ERROR;
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
