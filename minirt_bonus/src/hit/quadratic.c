/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:05:01 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 14:51:56 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resolve_hit(t_hit *hit, t_quad quad)
{
	hit->hit = true;
	if (quad.t1 < EPS && quad.t2 < EPS)
		hit->hit = false;
	else if (quad.t1 > EPS)
		hit->t = quad.t1;
	else
		hit->t = quad.t2;
}

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
