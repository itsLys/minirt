/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 16:08:14 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, err, ft_strlen(err));
}

void	exit_error(char *msg) 
{
	// free_all
	print_error(msg);
	exit(FAILIURE);
}
