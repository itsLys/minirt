/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:29:57 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/23 11:30:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (err)
		write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, ERR_USAGE, ft_strlen(ERR_USAGE));
}
