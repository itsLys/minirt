/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:43:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:44:12 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

#include "types.h"

void		destroy_mlx(t_data *data);
void		init_mlx(t_data *data);
void		setup_mlx(t_data *data);
int			render_img(t_data *data);

#endif // !MLX_H
