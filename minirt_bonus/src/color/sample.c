/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:34:10 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/10 09:07:16 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	sample_bg_color(int x, int y, t_texture *tx)
{
	t_vec2	coords;

	coords.x = x / (WIDTH - 1.0);
	coords.y = y / (HEIGHT - 1.0);

	coords.x = fmod(coords.x * 1.0, 1.0);
	coords.y = fmod(coords.y * 1.0, 1.0);

	return sample_tx_color(coords,  tx);
}

