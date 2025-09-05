/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:47:26 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H


# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include <mlx.h>

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
# include "mlx.h"



// vec3 ops

// BUG: testing debugging
void		print_scene(t_data *data);
void		print_ray(int x, int y, t_ray ray);
void		print_vec3(t_vec3 vec);
// BUG: END

// mlx

// map pixel
t_ray		map_pixel(int x, int y, t_data *data);

// camera
void		init_cam(t_cam *cam);

// hooks
// int			handle_keypress(int code, t_data *data);
// int			handle_keyrelease(int code, t_data *data);
// int			handle_button(int code, int x, int y, t_data *data);

// render
void		draw_image(t_data *data);

// object

// parse

// error
void		print_error(char *err);
void		exit_error(char *msg, t_data *data);

// exit
int			clean_exit(t_data *data, int status);

// geters

// init: STAY HERE
void		init_ambient_light(char *line, t_data *data);
void		init_camera(char *line, t_data *data);
void		init_light(char *line, t_data *data);
void		init_plane(char *line, t_data *data);
void		init_sphere(char *line, t_data *data);
void		init_cylinder(char *line, t_data *data);
void		init_data(t_data *data);
void		init_cam_rays(t_data *data);
void		destroy_cam_rays(t_cam_rays rays);
void		set_directions(t_cam_rays *rays, t_data *data);
void		set_offsets(t_vec2 **offsets, t_data *data);

// camera
void		setup_viewport(t_cam *cam);

// intersect
// int			check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy);
// intersect utils

// hit
void		record_hit(t_obj **obj, t_hit *hit, t_ray ray);
t_rgb		trace_ray(t_ray ray, t_data *data);

// quadratic
void		solve_quadratic(t_quad *quad);

// color

// utils
// bool		is_close(double n, double m);
// bool		greater_than(double n, double m);
// bool		is_less_then(double n, double m);

// handlers
// void		handle_props(int code, t_data *data);
// void		handle_obj_move(int code, t_data *data);
// void		handle_cam_rotate(int code, t_cam *cam);
// void		handle_obj_rotate(int code, t_obj *obj, t_cam cam);

#endif
