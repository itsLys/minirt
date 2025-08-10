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

int ft_isspace(int a)
{
	return (a == 31 || (a >= 9 && a <=13));
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

int	get_double(char **line, int l) // 12.34
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

int	ambient_light(char *line, t_light *amb)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	amb->ratio = get_double(&(line + i), 0);
	while (ft_isspace(line[i]))
		i++;
	if (get_color(line + i, &amb->color))
		return (ERROR);
}

int	process_line(char *line, t_data *data)
{
	int	i;
	
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'A' && ft_isspace(line[i + 1])
		&& !ambient_light(line + 1, &data->amb))
			return ERROR;
	else if (line[i] == 'C' && ft_isspace(line[i + 1])
		&& !camera(line + 1, data))
			return ERROR;
	else if (line[i] == 'L' && ft_isspace(line[i + 1])
		&& !source_light(line + 1, data))
			return ERROR;
	else if (ft_strncmp(line, "pl", 2) && ft_isspace(line[i + 2])
		&& !plane(line + 2, data))
			return ERROR;
	else if (ft_strncmp(line, "sp", 2) && ft_isspace(line[i + 2])
		&& !sphere(line + 2, data))
			return ERROR;
	else if (ft_strncmp(line, "cy", 2) && ft_isspace(line[i + 2])
		&& !cylinder(line + 2, data))
			return ERROR;
	return ERROR;
}
