/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:17:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 12:56:51 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[i] == 'A' && ft_isspace(line[i + 1]))
		parse_ambient_light(line + 1, data);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		parse_camera(line + 1, data);
	else if (line[i] == 'l' && ft_isspace(line[i + 1]))
		parse_light(line + 1, data);
	else if (line[i] == 't' && ft_isspace(line[i + 1]))
		parse_texture(line + 1, data);
	else if (!ft_strncmp(line, "pl", 2) && ft_isspace(line[i + 2]))
		parse_plane(line + 2, data);
	else if (!ft_strncmp(line, "sp", 2) && ft_isspace(line[i + 2]))
		parse_sphere(line + 2, data);
	else if (!ft_strncmp(line, "cy", 2) && ft_isspace(line[i + 2]))
		parse_cylinder(line + 2, data);
	else if (!ft_strncmp(line, "cn", 2) && ft_isspace(line[i + 2]))
		parse_cone(line + 2, data);
	else if (!ft_strncmp(line, "rc", 2) && ft_isspace(line[i + 2]))
		parse_rectangle(line + 2, data);
	else
		return (exit_error(ERR_PARAM, data), ERROR);
	return (SUCCESS);
}

int	parse_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (init_config(line + i, data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
