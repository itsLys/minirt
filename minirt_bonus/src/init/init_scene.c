/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:56:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/16 10:57:32 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* int	get_integer(char **line, t_data *data)
   {
   int	n;
   int	i;

   i = 0;
   while (ft_isspace(**line))
   (*line)++;
   n = parse_num(*line);
   while (ft_isdigit(**line))
   {
   (*line)++;
   i = 1;
   }
   if (i == 0)
   exit_error(ERR_INT, data);
   return (n);
   } */

/* t_vec3	get_vec3(char **line, t_data *data)
   {
   t_vec3	vec3;

   vec3.x = get_double(line, data);
   if (*(*line)++ != ',')
   exit_error(ERR_COORDS, data);
   vec3.y = get_double(line, data);
   if (*(*line)++ != ',')
   exit_error(ERR_COORDS, data);
   vec3.z = get_double(line, data);
   return (vec3);
   } */
# define ERR_TEXTURE "dsa"
# define ERR_REL_PATH "dsa"

char *get_string(char **line, t_data *data)
{
	char str[PATH_MAX];
	int i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
	if ((**line) == '\n')
		return NULL;
	while (ft_isalnum(**line) && i < PATH_MAX)
	{
		str[i++] = **line;
		(*line)++;
	}
	if (i == PATH_MAX)
		return  NULL;
	str[i] = 0;
	return NULL;
}
// TODO: complete getting the string and texture

t_texture	get_texture(char **line, t_data *data)
{
	char	*path;

	path = get_string(line, data);
	if (path == NULL)
		return (t_texture) {0}; // WARN: actually return the texture variable with img pointer set to null
	if (path && path[0] == '/')
		exit_error(ERR_TEXTURE ERR_REL_PATH, data);

	return (t_texture) {0};
}

void	init_ambient_light(char *line, t_data *data)
{
	double		ratio;
	t_rgb		rgb;
	t_texture	texture;

	if (data->scene.amb_light.on == true)
		exit_error(ERR_AMB_LIGHT ERR_MULTI, data);
	ratio = get_double(&line, data);
	rgb = get_rgb(&line, data);
	texture	= get_texture(&line, data);
	if (ratio < 0.0 || ratio > 1.0)
		exit_error(ERR_AMB_LIGHT ERR_RATIO, data);
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
	data->scene.amb_light.on = true;
	data->scene.amb_light.ratio = ratio;
	data->scene.amb_light.color = rgb;
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

void	init_data(t_data *data)
{
	data->texture.ptr = NULL;
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
	data->render_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	data->mapping_workers = malloc(sizeof(t_worker) * SPLIT * SPLIT);
	if (data->render_workers == NULL || data->mapping_workers == NULL)
		exit_error(NULL, data);
	init_workers(data->mapping_workers, data, work_directions);
	init_workers(data->render_workers, data, work_rendering);
	// NOTE: maybe should not be here
}
