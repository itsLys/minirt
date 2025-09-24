/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:14:16 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 13:15:13 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

#include "types.h"

void	rotate_tilt(int code, t_local_coords *coords);
void	rotate_turn(int code, t_local_coords *coords);
void	rotate_spin(int code, t_local_coords *coords);
void	handle_translate(int code, t_vec3 *point, t_cam cam);

#endif // !TRANSFORM_H
