/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:22:30 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:34:30 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

#include "types.h"

void		init_ambient_light(char *line, t_data *data);
void		init_cam(t_cam *cam);
void		init_camera(char *line, t_data *data);
void		init_light(char *line, t_data *data);
void		init_plane(char *line, t_data *data);
void		init_sphere(char *line, t_data *data);
void		init_cylinder(char *line, t_data *data);
void		init_data(t_data *data);
void		init_offsets(t_vec2	**offsets, t_data *data);
void		init_cam_rays(t_data *data);

#endif // !INIT_H
