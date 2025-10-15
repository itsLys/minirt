/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:32:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:33:35 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "types.h"

void	print_scene(t_data *data);
void	print_light(t_obj *obj);
void	print_cn(t_obj *obj);
void	print_cy(t_obj *obj);
void	print_pl(t_obj *obj);
void	print_sp(t_obj *obj);
void	print_rc(t_obj *obj);
void	print_vec3(t_vec3 vec);
void	print_color_props(t_obj *obj);
void	print_camera(t_cam cam);
void	print_amb_light(t_amb_light amb);
void	print_textures(t_texture *lst);

#endif // !PRINT_H
