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
	int		fd;
	char	*line;

	if (check_file_ext(filename) == ERROR)
		return (ERROR);
	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return (exit_error(strerror(errno), data), ERROR);
	while (1)
	{
		line = get_next_line(fd);
		while (line && ft_strisempty(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line == NULL)
			break ;
		if (parse_line(line, data) == ERROR)
			return (ERROR);
		free(line);
	}
	return (SUCCESS);
}
