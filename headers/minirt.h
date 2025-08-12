/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/11 16:07:24 by ihajji           ###   ########.fr       */
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
# include <stdbool.h>

# define EXT ".rt"

// ERR OBJS
# define ERR_AMB_LIGHT "Ambient: "
# define ERR_CAM "Camera: "
# define ERR_CY "Cylinder: "
# define ERR_PL "Plane: "
# define ERR_LIGHT "Light: "
# define ERR_PARAM "Wrong parameter field\n"


// ERR PARAMS
# define ERR_RGB "RGB is not correct\n"
# define ERR_DBL "Double is not correct\n"
# define ERR_INT "Integer is not correct\n"
# define ERR_RATIO "Ratio is not correct"
# define ERR_NORM_VAL "Normalized value is not correct\n"
# define ERR_FOV "Fov is not correct\n"
# define ERR_COORDS "Wrong coordination form\n"

// # define MAX_OBJECT 99
typedef enum s_obj_type
{
	T_SP,
	T_PL,
	T_CY,
	T_LS,
}	t_obj_type;

typedef	struct s_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef union u_rgb
{
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	uint32_t	rgba;
}	t_rgb;

typedef struct s_light
{
	double	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_cam
{
	t_coords	pos;
	t_coords	norm;
	int			fov;
}	t_cam;

typedef struct s_light_src
{
	double ratio;
}	t_light_src;

typedef struct s_sp
{
	double		d;
}	t_sp;

typedef struct s_pl
{
	t_coords	norm;
}	t_pl;

typedef struct s_cy
{
	t_coords	norm;
	double		d;
	double		h;
}	t_cy;

typedef struct s_obj
{
	t_obj_type	type;
	t_coords	pos;
	t_rgb		color;
	void		*shape;
}	t_obj;

typedef struct s_scene
{
	t_light			amb_light;
	t_cam			cam;
	t_obj			*objs;
}	t_scene;

typedef struct s_data
{
	t_scene scene;
}	t_data ;

// parse
int			process_line(char *line, t_data *data);
int			parse_file(char *filename, t_data *data);

// error and exit
void		print_error(char *err);
void		exit_error(char *msg);

// geters
double		get_double(char **line);
t_rgb		get_rgba(char **line);
t_coords	get_vec3(char **line);
int			get_integer(char **line);

// init
void		init_ambient_light(char *line, t_data *data);
void		init_camera(char *line, t_data *data);
void		init_source_light(char *line, t_data *data);
void		init_plane(char *line, t_data *data);
void		init_sphere(char *line, t_data *data);
void		init_cylinder(char *line, t_data *data);

// vec3 ops
double		vec3_len(t_coords v);

#endif
