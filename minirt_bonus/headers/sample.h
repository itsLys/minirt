/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:31:20 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:31:46 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLE_H
# define SAMPLE_H

#include "types.h"

t_vec3		world_to_local(t_hit hit, t_local_coords coords);
t_vec2		compute_texture_ratio(t_hit hit);
void		apply_bump_map(t_hit *hit, t_vec2 crds);
t_rgb		sample_tx_color(t_vec2 coords, t_texture *tx);
t_rgb		sample_bg_color(int x, int y, t_texture *tx);

#endif // !SAMPLE_H
