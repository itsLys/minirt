/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:22:30 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:30:05 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "types.h"

void	init_ambient_light(char *line, t_data *data);
void	init_camera(char *line, t_data *data);
void	init_light(char *line, t_data *data);
void	init_plane(char *line, t_data *data);
void	init_sphere(char *line, t_data *data);
void	init_cylinder(char *line, t_data *data);
void	init_cone(char *line, t_data *data);
void	init_data(t_data *data);
void	init_offsets(t_vec2 **offsets, t_data *data);
void	init_cam_rays(t_data *data);
int		init_program(char *file, t_data *data);
void	init_window(t_data *data);

// TODO: change location
void	setup_cam_coords(t_cam *cam);
#endif // !INIT_H
