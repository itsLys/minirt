/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:26:15 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:30:36 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "types.h"

t_ray	map_pixel(int x, int y, t_cam cam, t_data *data);
t_rgb	trace_ray(t_ray ray, t_data *data);
void	record_hit(t_obj **obj, t_hit *hit, t_ray ray);

#endif // !RAY_H
