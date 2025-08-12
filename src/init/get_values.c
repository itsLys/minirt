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

# define ERR_COORDS "Wrong coordination form\n"

double	get_double(char **line)
{
	int		i;
	double	f;

	i = 0;
	if (*line[i] == '-' || *line[i] == '+')
		i++;
	if (!ft_isdigit(*line[i]))
		exit_error(ERR_COORDS);
	f = ft_atof(*line); // atof take (char *) not (char **)!
	return (f);
}

t_coords    get_vec3(char **line) // case 1,,0 or 1,, check inside get double if **line is digit or '+/-'digit 
{
	t_coords	vec3;

	while (ft_isspace(**line))
		(*line)++;
	vec3.x = get_double(**line);
	if (**line != ',')
		exit_error(ERR_COORDS);
	vec3.y = get_double(**line);
	if (**line != ',')
		exit_error(ERR_COORDS);
	vec3.z = get_double(**line);
	return (vec3);
}

