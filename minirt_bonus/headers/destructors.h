/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:04:39 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/20 16:06:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTRUCTORS_H

# define DESTRUCTORS_H

# include "types.h"

void	destroy_workers(t_data *data);
void	destroy_objects(t_obj **lst);
void	destroy_textures(void *mlx, t_texture **lst);
void	destroy_scene(t_data *data);

#endif // !DESTRUCTORS_H
