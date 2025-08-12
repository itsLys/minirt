/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/12 20:16:58 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, err, ft_strlen(err));
}

void	exit_error(char *msg, t_data *data)
{
	obj_lst_free(data->scene.obj_list);
	if (msg)
		print_error(msg);
	exit(FAILIURE);
}

void clean_exit(t_data *data)
{
	obj_lst_free(data->scene.obj_list);
}
