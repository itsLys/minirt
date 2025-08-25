/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:07:37 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/20 17:09:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb compute_amb(t_rgb color, t_light amb_light)
{
	t_rgb amb;

	amb.r = (color.r * amb_light.ratio) * amb_light.color.r;
	amb.g = (color.g * amb_light.ratio) * amb_light.color.g;
	amb.b = (color.b * amb_light.ratio) * amb_light.color.b;
	return amb;
}

