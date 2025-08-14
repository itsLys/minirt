/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/14 16:28:20 by yel-guad         ###   ########.fr       */
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
	print_error(msg);
	clean_exit(data, FAILIURE);
}
