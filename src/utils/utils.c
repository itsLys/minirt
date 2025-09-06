/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:59:24 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/23 10:59:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_close(double n, double m)
{
	return (fabs(n - m) < EPS);
}

bool	is_less_then(double n, double m)
{
	if (fabs(n - m) < EPS)
		return (false);
	return (n < m);
}

bool	greater_than(double n, double m)
{
	if (fabs(n - m) < EPS)
		return (false);
	return (n > m);
}
