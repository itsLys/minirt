/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:53:50 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/19 11:13:46 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CLEAR "\033[K\r"

static void	print_current_line(void)
{
	static int	i;

	printf(CLEAR "current line:	%d", ++i);
}

int	parse_file(char *filename, t_data *data)
{
	if (check_file_ext(filename) == ERROR)
		return (exit_error(ERR_FILE_EXTENSION, data), ERROR);
	data->fd = open(filename, O_RDONLY);
	if (data->fd == ERROR)
		return (exit_error(strerror(errno), data), ERROR);
	while (1)
	{
		data->line = get_next_line(data->fd);
		print_current_line();
		while (data->line && ft_strisempty(data->line))
		{
			free(data->line);
			data->line = get_next_line(data->fd);
			print_current_line();
		}
		if (data->line == NULL)
			break ;
		if (parse_line(data->line, data) == ERROR)
			return (ERROR);
		free(data->line);
		data->line = NULL;
	}
	get_next_line(FREE_BUFFER);
	return (SUCCESS);
}
