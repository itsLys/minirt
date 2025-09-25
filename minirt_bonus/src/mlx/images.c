/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:41:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 15:46:24 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	img_get_pixel(t_img img, int x, int y)
{
	char	*pixel;

	pixel = img.addr + (y * img.line_len + x * (img.bpp / 8));
	return int_to_rgb((*(int *)pixel));
}

void	img_put_pixel(t_img img, int x, int y, t_rgb color)
{
	char	*pixel;

	pixel = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(int *)pixel = rgb_to_int(color);
}
