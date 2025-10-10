/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:56:08 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:33:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_num(char *str)
{
	int	n;

	n = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str && *str >= '0' && *str <= '9')
		n = (*(str++) - '0') + n * 10;
	return (n);
}

int	get_integer(char **line, t_data *data)
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
}

double	get_double(char **line, t_data *data)
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
		exit_error(ERR_DBL, data);
	return (f);
}
