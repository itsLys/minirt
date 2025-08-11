/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:35:07 by yel-guad          #+#    #+#             */
/*   Updated: 2025/08/10 18:04:34 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int ft_isspace(int c)
{
	return (c == ' ' || c == '\t');
}

int	get_vect(char *line, t_light amb)
{
	
}

int	get_number(char **line, int l)
{
	int (i), (j), (n);

	i = 0;
	n = 0;
	while (ft_isdigit(*line[i]))
		i++;
	if (l && line[i] != ',')
		return ERROR;
	j = 0;
	while (j < i)
	{
		n = n * 10 + *line[j] - '0';
		j++; 
	}
	return (n);
}

int	get_color(char *line, t_rgb *color)
{
	color->r = get_number(&line, TRUE);
	if (color->r == ERROR)
		return (ERROR);
	color->g = get_number(&line, TRUE);
	if (color->g == ERROR)
		return (ERROR);
	color->b = get_number(&line, FALSE);
	if (color->b == ERROR)
		return (ERROR);
}

double	get_double(char **line) // 12.34
{
	double	db;

	int (i), (j);
	i = 0;
	db = 0;
	while (ft_isdigit(*line[i]))
		i++;
	if (*line[i] != '.')
		return (ERROR);
	// if (l && line[i] != ',')
	// 	return ERROR;
	j = 0;
	while (j < i)
	{
		db = db * 10 + *line[j] - '0';
		j++;
	}
	return (db);
}

int	init_ambient_light(char *line, t_data *data)
{
	// int	i;
	//
	// i = 0;
	// while (ft_isspace(line[i]))
	// 	i++;
	// while (ft_isspace(line[i]))
	// 	i++;
	data->scene.amb_light.ratio = get_double(&line);
	if (get_color(line + i, &amb->color))
		return (ERROR);
}
// A 	0.2							255,255,255
// data-light_raio = get_double()
// data-light_color = get_colors()
// data-light_color = get_colors()
// data-light_color = get_colors()

int init_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[i] == 'A' && ft_isspace(line[i + 1])
			&& !init_ambient_light(line + 1, data))
		return ERROR;
	else if (line[i] == 'C' && ft_isspace(line[i + 1])
			&& !init_camera(line + 1, data))
		return ERROR;
	else if (line[i] == 'L' && ft_isspace(line[i + 1])
			&& !init_source_light(line + 1, data))
		return ERROR;
	else if (ft_strncmp(line, "pl", 2) && ft_isspace(line[i + 2])
			&& !init_plane(line + 2, data))
		return ERROR;
	else if (ft_strncmp(line, "sp", 2) && ft_isspace(line[i + 2])
			&& !init_sphere(line + 2, data))
		return ERROR;
	else if (ft_strncmp(line, "cy", 2) && ft_isspace(line[i + 2])
			&& !init_cylinder(line + 2, data))
		return ERROR;
	else
		return ERROR;
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
}
