/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:21:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:21:00 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_program(char *file, t_data *data)
{
	init_data(data);
	init_mlx(data);
	if (parse_file(file, data) == ERROR)
		return (ERROR);
	init_window(data);
	return (SUCCESS);
}
