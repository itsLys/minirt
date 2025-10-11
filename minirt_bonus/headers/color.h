/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:29:46 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:30:45 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "types.h"

// rgb ops
t_rgb		rgb(double r, double g, double b);
t_rgb		rgb_add(t_rgb c1, t_rgb c2);
t_rgb		rgb_mult(t_rgb c1, t_rgb c2);
t_rgb		rgb_scale(double k, t_rgb c);
t_rgb		rgb_clamp(t_rgb c);
t_rgb		int_to_rgb(int c);
int			rgb_to_int(t_rgb c);

// compute
t_rgb		compute_color(t_ray ray, t_hit hit, t_data *data);
t_rgb		compute_amb(t_rgb obj, t_amb_light amb);
t_rgb		compute_defuse(t_hit hit, t_obj *light_obj, t_light *light);
t_rgb		compute_spacular(t_hit hit, t_obj *l_obj, t_light *light,
		t_cam cam);
t_rgb		compute_light(t_hit hit, t_obj *l_obj, t_light *light,
		t_data *data);
t_rgb		compute_lights(t_hit hit, t_data *data);

// utils
bool		is_shadow(t_hit hit, t_obj *light, t_data *data);

#endif // ! COLOR_H
