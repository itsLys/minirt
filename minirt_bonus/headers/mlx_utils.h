/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:43:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:50:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "types.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>

void	destroy_mlx(t_data *data);
void	init_mlx(t_data *data);
void	setup_hooks(t_data *data);
int		render_img(t_data *data);
void	draw_image(t_data *data, t_int_vec2 start, t_int_vec2 end);

#endif // !MLX_UTILS_H
