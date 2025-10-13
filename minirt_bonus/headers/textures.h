/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:20:33 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 16:34:38 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

#include "types.h"

void		texture_add(t_texture *tx, t_texture **list);
t_texture	*find_tx(char *name, t_texture *lst);
t_vec2	sphere_ratio(t_hit hit, t_sp *sp);
t_vec2	cylinder_ratio(t_hit hit, t_cy *cy);
t_vec2	plane_ratio(t_hit hit, t_pl *pl);
t_vec2	cone_ratio(t_hit hit, t_cn *cn);
t_vec2	rectangle_ratio(t_hit hit, t_rc *rc);

#endif // !TEXTURES_H

