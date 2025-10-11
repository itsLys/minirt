/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:12:10 by yel-guad          #+#    #+#             */
/*   Updated: 2025/09/06 16:35:34 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_double_parameter(char **line, t_data *data)
{
	while (ft_isspace(**line))
		(*line)++;
	return (get_double(line, data));
}

int	get_integer(char **line, t_data *data)
{
	int	n;
	int	i;

	i = 0;
	n = parse_num(*line);
	while (ft_isdigit(**line))
	{
		(*line)++;
		i = 1;
	}
	if (i == 0)
		exit_error(ERR_INT, data);
	return (n);
}

t_rgb	get_rgb(char **line, t_data *data)
{
	t_rgb	rgb;
	int		tmp;

	while (ft_isspace(**line))
		(*line)++;
	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.r = tmp / 255.0;
	if (*(*line)++ != ',')
		exit_error(ERR_RGB, data);
	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.g = tmp / 255.0;
	if (*(*line)++ != ',')
		exit_error(ERR_RGB, data);
	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.b = tmp / 255.0;
	return (rgb);
}

double	get_double(char **line, t_data *data)
{
	double	f;
	int		i;

	i = 0;
	f = ft_atof(*line);
	if (**line == '-' || **line == '+')
		(*line)++;
	while (ft_isdigit(**line))
	{
		(*line)++;
		i = 1;
	}
	if (*(*line) == '.')
		(*line)++;
	while (ft_isdigit(**line))
		(*line)++;
	if (i == 0)
		exit_error(ERR_DBL, data);
	return (f);
}

t_vec3	get_vec3(char **line, t_data *data)
{
	t_vec3	vec3;

	while (ft_isspace(**line))
		(*line)++;
	vec3.x = get_double(line, data);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS, data);
	vec3.y = get_double(line, data);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS, data);
	vec3.z = get_double(line, data);
	return (vec3);
}
