/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:53:50 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:27:57 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_file(char *filename, t_data *data)
{
	char	*line;

	if (check_file_ext(filename) == ERROR)
		return (ERROR);
	data->fd = open(filename, O_RDONLY);
	if (data->fd == ERROR)
		return (exit_error(strerror(errno), data), ERROR);
	while (1)
	{
		line = get_next_line(data->fd);
		while (line && ft_strisempty(line))
		{
			free(line);
			line = get_next_line(data->fd);
		}
		if (line == NULL)
			break ;
		if (parse_line(line, data) == ERROR)
			return (ERROR);
		free(line);
	}
	return (SUCCESS);
}
