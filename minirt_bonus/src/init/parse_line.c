/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:17:38 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 11:09:52 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


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

int	process_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (init_config(line + i, data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
