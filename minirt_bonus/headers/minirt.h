/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/30 16:42:37 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// WARN: check existence of the file
#define XPM "../moon.xpm"

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include <pthread.h>

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
# include "threads.h"
# include "destructors.h"
# include "transform.h"
# include "textures.h"

// BUG: testing debugging
void		print_scene(t_data *data);
void		print_ray(int x, int y, t_ray ray);
void		print_vec3(t_vec3 vec);
void	print_obj_type(t_obj *obj);
// BUG: END

// void	init_texture(t_data *data);

void	skip_trailing(char *line, t_data *data);
void	texture_add(t_texture *tx, t_texture **list);

void	init_texture(char *line, t_data *data);
void	img_put_pixel(t_img img, int x, int y, t_rgb color);
t_rgb	img_get_pixel(t_img img, int x, int y);
t_rgb compute_avg(t_texture	*tx);
t_rgb sample_tx_color(t_vec2 coords, t_texture *tx);
t_rgb	sample_color(t_hit hit);
t_vec3 world_to_local(t_hit hit, t_local_coords coords);
t_rgb	sample_sp_color(t_hit hit, t_sp *sp);
t_rgb	sample_cy_color(t_hit hit, t_cy *cy);
t_rgb	sample_pl_color(t_hit hit);
t_rgb	sample_bg_color(int x, int y, t_texture *tx);
t_rgb	compute_amb(t_rgb obj, t_amb_light amb);
t_rgb	compute_defuse(t_hit hit, t_obj *light_obj, t_light *light);
t_rgb compute_spacular(t_hit hit, t_obj *l_obj, t_light *light, t_cam cam);
t_rgb compute_light(t_hit hit, t_obj *l_obj, t_light *light, t_data *data);
t_rgb	compute_lights(t_hit hit, t_data *data);
bool	is_shadow(t_hit hit, t_obj *light, t_data *data);

#endif
