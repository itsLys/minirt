/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:53:50 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:19:22 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_file_ext(char *filename)
{
	char	*ext;

	ext = ft_strnstr(filename, EXT, ft_strlen(filename));
	if (ext == NULL)
		return (ERROR);
	if (ext[3])
		return (ERROR);
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

int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;

	data->scene.obj_list = malloc(sizeof(t_obj *));
	*(data->scene.obj_list) = NULL;
	if (check_file_ext(filename) == ERROR)
		return (ERROR);
	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return (print_error(strerror(errno)), ERROR);
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
		if (process_line(line, data) == ERROR)
			return (ERROR);
		free(line);
	}
	return (SUCCESS);
}
