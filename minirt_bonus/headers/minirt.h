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

// WARN: check existence of the file
#define XPM "../sky.xpm"

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

// BUG: testing debugging
void		print_scene(t_data *data);
void		print_ray(int x, int y, t_ray ray);
void		print_vec3(t_vec3 vec);
void	print_obj_type(t_obj *obj);
// BUG: END

void	init_texture(t_data *data);
void	init_threads(t_worker *worker);
void	join_threads(t_worker *worker);
void	set_worker_bounds(t_worker *worker);
void	init_mapping_workers(t_data *data);

#endif
