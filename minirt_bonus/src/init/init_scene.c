/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/20 16:18:30 by ihajji           ###   ########.fr       */
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
	tx_name = get_string(&line, data); // FIX: free this
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	data->scene.amb.on = true;
	data->scene.amb.ratio = ratio;
	data->scene.amb.color = rgb;
	data->scene.amb.tx_name = tx_name;
}

t_texture_type	get_type(char **line, t_data *data)
{
	char			*str;
	t_texture_type	type;

	str = get_string(line, data);
	if (str == NULL)
		exit_error(NULL, data);
	if (ft_strcmp("bump", str) == 0)
		type = BUMP_TX;
	else if (ft_strcmp("color", str) == 0)
		type = COLOR_TX;
	else
		type = INVALID_TX;
	return type;
}

// TODO: make a tx destructor
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
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
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
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
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
	else if (line[i] == 't' && ft_isspace(line[i + 1]))
		init_texture(line + 1, data);
	// else if (line[i] == 'c' && ft_isspace(line[i + 1]))
	// 	init_pattern(line + 1, data);
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

void	init_scene(t_data *data)
{
	data->scene.light_on = false;
	data->scene.amb.on = false;
	data->scene.cam.on = false;
	data->scene.selected.type = T_CAM;
	data->scene.selected.light = NULL;
	data->scene.tx_lst = malloc(sizeof(t_texture *));
	data->scene.patt_lst = malloc(sizeof(t_pattern *));
	data->scene.obj_lst = malloc(sizeof(t_obj *));
	// FIX: CONTINUEHERE
	if (data->scene.obj_lst == NULL
		|| data->scene.)
	*(data->scene.obj_lst) = NULL;
	*(data->scene.tx_lst) = NULL;
	*(data->scene.patt_lst) = NULL;
}

void	init_data(t_data *data)
{
	init_scene(data);
	data->mlx = NULL;
	data->img.img = NULL;
	data->win = NULL;
	data->offsets = NULL;
	data->rays.dirs = NULL;
	data->render_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	data->mapping_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	if (data->render_workers == NULL || data->mapping_workers == NULL)
		exit_error(NULL, data);
	init_workers(data->mapping_workers, data, work_directions);
	init_workers(data->render_workers, data, work_rendering);
	// NOTE: maybe should not be here
}
