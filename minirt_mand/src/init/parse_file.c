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

int	parse_num(char *str)
{
	int	n;

	n = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str && *str >= '0' && *str <= '9')
		n = (*(str++) - '0') + n * 10;
	return (n);
}

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
	data->scene.obj_list = malloc(sizeof(t_obj *));
	*(data->scene.obj_list) = NULL;
	if (check_file_ext(filename) == ERROR)
		return (ERROR);
	data->fd = open(filename, O_RDONLY);
	if (data->fd == ERROR)
		return (print_error(strerror(errno)), ERROR);
	while (1)
	{
		data->line = get_next_line(data->fd);
		while (data->line && ft_strisempty(data->line))
		{
			free(data->line);
			data->line = get_next_line(data->fd);
		}
		if (data->line == NULL)
			break ;
		if (process_line(data->line, data) == ERROR)
			return (ERROR);
		free(data->line);
	}
	return (SUCCESS);
}
