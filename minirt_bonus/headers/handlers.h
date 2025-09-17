/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:36 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:44:57 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H 

# include "types.h"

int			handle_keypress(int code, t_data *data);
int			handle_keyrelease(int code, t_data *data);
int			handle_button(int code, int x, int y, t_data *data);
void		handle_props(int code, t_data *data);
void		handle_obj_move(int code, t_data *data);
void		handle_coords_rotate(int code, t_local_coords *coords);
// NOTE: deprecated
// void		handle_cam_rotate(int code, t_cam *cam);
// void		handle_obj_rotate(int code, t_obj *obj, t_cam cam);

#endif // !HANDLERS_H
