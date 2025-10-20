/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:32:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>

# include "constants.h"
# include "error.h"
# include "types.h"
# include "color.h"
# include "vec3.h"
# include "intersect.h"
# include "handlers.h"
# include "object.h"
# include "parse.h"
# include "utils.h"
# include "mlx_utils.h"
# include "init.h"
# include "scene.h"
# include "ray.h"

void		print_scene(t_data *data);
void		print_cy(t_obj *obj);
void		print_pl(t_obj *obj);
void		print_sp(t_obj *obj);
void		print_color_props(t_obj *obj);
void		print_vec3(t_vec3 vec);
void		print_camera(t_cam cam);
void		print_light(t_light light);
void		print_amb_light(t_light amb);

#endif
