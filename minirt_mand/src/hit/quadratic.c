/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:05:01 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/20 17:05:08 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	solve_quadratic(t_quad *quad)
{
	double	delta;

	delta = quad->b * quad->b - 4 * quad->a * quad->c;
	if (delta < 0)
	{
		quad->t1 = -1.0;
		quad->t2 = -1.0;
	}
	else
	{
		quad->t1 = (-quad->b - sqrt(delta)) / (2 * quad->a);
		quad->t2 = (-quad->b + sqrt(delta)) / (2 * quad->a);
	}
}
