/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:43:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:28:41 by ihajji           ###   ########.fr       */
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
void	init_window(t_data *data);
void	setup_hooks(t_data *data);
int		render_img(t_data *data);
void	draw_image(t_data *data, t_int_vec2 start, t_int_vec2 end);

// mlx images
void	img_put_pixel(t_img img, int x, int y, t_rgb color);
t_rgb	img_get_pixel(t_img img, int x, int y);

#endif // !MLX_UTILS_H
