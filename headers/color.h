/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:29:46 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:37:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  COLOR_H
# define COLOR_H

#include "types.h"

// rgb ops
t_rgb		rgb(double r, double g, double b);
t_rgb		rgb_add(t_rgb c1, t_rgb c2);
t_rgb		rgb_mult(t_rgb c1, t_rgb c2);
t_rgb		rgb_scale(double k, t_rgb c);
t_rgb		rgb_clamp(t_rgb c);
t_rgb		int_to_rgb(int c);
int			rgb_to_int(t_rgb c);

// compute
t_rgb		compute_color(t_hit hit, t_data *data);
t_rgb		compute_amb(t_rgb color, t_light amb_light);

#endif // ! COLOR_H
