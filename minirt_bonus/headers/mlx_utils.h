/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:43:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/19 10:54:41 by yel-guad         ###   ########.fr       */
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
int		render_img(t_data *data);
void	draw_image(t_data *data, t_int_vec2 start, t_int_vec2 end);

void	setup_hooks(t_data *data);
void	handle_held_keys1(t_data *data);
void	handle_held_keys2(t_data *data);

// mlx images
void	img_put_pixel(t_img img, int x, int y, t_rgb color);
t_rgb	img_get_pixel(t_img img, int x, int y);

#endif // !MLX_UTILS_H
