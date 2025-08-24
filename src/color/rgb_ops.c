/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:13:41 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/24 10:45:37 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rgb(double r, double g, double b)
{
	t_rgb c;

	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

t_rgb	rgb_add(t_rgb c1, t_rgb c2)
{
	return rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

t_rgb	rgb_mult(t_rgb c1, t_rgb c2)
{
	return rgb(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

t_rgb rgb_scale(double k, t_rgb c)
{
	return rgb(c.r * k, c.g * k, c.b * k);
}

t_rgb	rgb_clamp(t_rgb c)
{
	if (c.r < 0) c.r = 0;
	if (c.g < 0) c.g = 0;
	if (c.b < 0) c.b = 0;
	if (c.r > 1) c.r = 1;
	if (c.g > 1) c.g = 1;
	if (c.b > 1) c.b = 1;
	return c;
}

int	rgb_to_int(t_rgb c)
{
	int		r;
	int		g;
	int		b;

	c = rgb_clamp(c);
	r = (int)(c.r * 255.999);
	g = (int)(c.g * 255.999);
	b = (int)(c.b * 255.999);
	return (r << 16 | g << 8 | b);
}

t_rgb int_to_rgb(int c)
{
	t_rgb rgb;

	rgb.r = ((c >> 16) & 0xFF) / 255.0;
	rgb.g = ((c >> 8) & 0xFF) / 255.0;
	rgb.b = (c & 0xFF) / 255.0;
	return rgb;
}
