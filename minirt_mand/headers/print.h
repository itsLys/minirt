/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:17:07 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/20 12:13:57 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "types.h"

void		print_scene(t_data *data);
void		print_cy(t_obj *obj);
void		print_pl(t_obj *obj);
void		print_sp(t_obj *obj);
void		print_color_props(t_obj *obj);
void		print_vec3(t_vec3 vec);
void		print_camera(t_cam cam);
void		print_light(t_light light);
void		print_amb_light(t_light amb);

#endif // !PRINT_H
