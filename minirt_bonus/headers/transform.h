/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:14:16 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:17:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

#include "types.h"

void	rotate_y(int code, t_local_coords *coords);
void	rotate_z(int code, t_local_coords *coords);
void	rotate_x(int code, t_local_coords *coords);
void	handle_translate(int code, t_vec3 *point, t_cam cam);

#endif // !TRANSFORM_H
