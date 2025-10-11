/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:57:56 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 11:34:31 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_integer_parameter(char **line, t_data *data)
{
	while (ft_isspace(**line))
		(*line)++;
	return (get_integer(line, data));
}

double	get_double_parameter(char **line, t_data *data)
{
	while (ft_isspace(**line))
		(*line)++;
	return (get_double(line, data));
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
