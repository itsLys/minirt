/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:50:02 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include "types.h"

int		handle_keypress(int code, t_data *data);
int		handle_keyrelease(int code, t_data *data);
int		handle_button(int code, int x, int y, t_data *data);
void	handle_props(int code, t_data *data);
void	handle_obj_move(int code, t_data *data);
void	handle_coords_rotate(int code, t_local_coords *coords);
void	handle_sp_props(int code, t_sp *sp);
void	handle_cn_props(int code, t_cn *cn);
void	handle_cy_props(int code, t_cy *cy);
void	handle_rc_props(int code, t_rc *rc);
void	handle_light_props(int code, t_light *light);
void	handle_cam_props(int code, t_cam *cam);
void	select_next_light(t_data *data);
void	select_object(int x, int y, t_data *data);
#endif // !HANDLERS_H
