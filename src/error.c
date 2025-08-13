/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/13 09:51:54 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (err)
		write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, ERR_USAGE, ft_strlen(ERR_USAGE));
}

void	exit_error(char *msg, t_data *data)
{
	obj_lst_free(data->scene.obj_list);
	print_error(msg);
	exit(FAILIURE);
}

void clean_exit(t_data *data)
{
	obj_lst_free(data->scene.obj_list);
	exit(SUCCESS);
}
