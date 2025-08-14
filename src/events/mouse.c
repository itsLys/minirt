/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:35 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/14 15:59:30 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_button(int code, int x, int y, t_data *data)
{
	(void) x;
	(void) y;
	(void) data;
	printf("mouse button pressed: %d\n", code);
	return 0;
}
