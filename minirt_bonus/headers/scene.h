/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:27:13 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:27:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "types.h"

void		setup_viewport(t_cam *cam);
void		destroy_cam_rays(t_cam_rays rays);
void		set_directions(t_data *data, t_int_vec2 start, t_int_vec2 end);
void		set_offsets(t_vec2 **offsets, t_data *data);

#endif // !SCENE_H
