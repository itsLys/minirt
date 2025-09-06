/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:32:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 18:32:28 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_int(t_rgb c)
{
	int	r;
	int	g;
	int	b;

	c = rgb_clamp(c);
	r = (int)(c.r * 255.999);
	g = (int)(c.g * 255.999);
	b = (int)(c.b * 255.999);
	return (r << 16 | g << 8 | b);
}

t_rgb	int_to_rgb(int c)
{
	t_rgb	rgb;

	rgb.r = ((c >> 16) & 0xFF) / 255.0;
	rgb.g = ((c >> 8) & 0xFF) / 255.0;
	rgb.b = (c & 0xFF) / 255.0;
	return (rgb);
}
