/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:43:48 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:31:51 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
#include "types.h"

void		destroy_mlx(t_data *data);
void		init_mlx(t_data *data);
void		setup_mlx(t_data *data);
int			render_img(t_data *data);
void		draw_image(t_data *data);

#endif // !MLX_UTILS_H
