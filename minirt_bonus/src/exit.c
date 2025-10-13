/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/10 15:29:39 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	destroy_data(t_data *data)
{
	get_next_line(FREE_BUFFER);
	close(data->fd);
	free(data->line);
	destroy_scene(data);
	destroy_workers(data);
	destroy_mlx(data);
	if (data->rays.dirs)
		free(data->rays.dirs);
	if (data->offsets)
		free(data->offsets);
}

int	clean_exit(t_data *data, int status)
{
	destroy_data(data);
	exit(status);
}

void	print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (err)
		write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, ERR_USAGE, ft_strlen(ERR_USAGE));
}

void	exit_error(char *msg, t_data *data)
{
	print_error(msg);
	clean_exit(data, FAILIURE);
}
