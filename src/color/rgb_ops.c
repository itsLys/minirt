/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:13:41 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 18:37:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rgb(double r, double g, double b)
{
	t_rgb	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_rgb	rgb_add(t_rgb c1, t_rgb c2)
{
	return (rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_rgb	rgb_mult(t_rgb c1, t_rgb c2)
{
	return (rgb(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}

t_rgb	rgb_scale(double k, t_rgb c)
{
	return (rgb(c.r * k, c.g * k, c.b * k));
}

t_rgb	rgb_clamp(t_rgb c)
{
	if (c.r < 0)
		c.r = 0;
	else if (c.r > 1)
		c.r = 1;
	if (c.g < 0)
		c.g = 0;
	else if (c.g > 1)
		c.g = 1;
	if (c.b < 0)
		c.b = 0;
	else if (c.b > 1)
		c.b = 1;
	return (c);
}
