/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:12:10 by yel-guad          #+#    #+#             */
/*   Updated: 2025/08/12 08:47:04 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_num(char *str)
{
	int	n;

	n = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str && *str >= '0' && *str <= '9')
		n = (*(str++) - '0') + n * 10;
	// if (*str)
	// 	return (ERROR);
	return (n);
}

int	get_integer(char **line)
{
	int		n;
	int		i;

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
		exit_error(ERR_INT);
	return (n);
}

t_rgb	get_rgba(char **line)
{
	t_rgb	rgba;

	rgba.r = get_integer(line);
	if (*(*line)++ != ',')
		exit_error(ERR_RGB);
	rgba.g = get_integer(line);
	if (*(*line)++ != ',')
		exit_error(ERR_RGB);
	rgba.b = get_integer(line);
	return (rgba);
}

double	get_double(char **line)
{
	double	f;
	int		i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
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
		exit_error(ERR_DBL);
	return (f);
}

t_coords    get_vec3(char **line) // case 1,,0 or 1,, check inside get double if **line is digit or '+/-'digit 
{
	t_coords	vec3;

	vec3.x = get_double(line);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS);
	vec3.y = get_double(line);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS);
	vec3.z = get_double(line);
	return (vec3);
}
