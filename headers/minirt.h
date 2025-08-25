/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/24 10:46:35 by ihajji           ###   ########.fr       */
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
# include <stdbool.h>
# include <mlx.h>

# define EXT ".rt"

# define HEIGHT 800
# define WIDTH	800
# define MINIRT_PROJECT	"miniRT"

// colors
# define BG_COLOR 0x00101010
# define AMB_CONST 0.05

// defaults
# define DFLT_AMB_COLOR 0x00FFFFFF
# define DFLT_AMB_RATIO 0.5
# define DFLT_CAM_X 0.0
# define DFLT_CAM_Y 0.0
# define DFLT_CAM_Z 9.0

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

// epsilon
#define EPS 1e-6

// ERR USAGE
# define ERR_USAGE \
	"A <ratio> <R,G,B>\n" \
	"C <x,y,z> <orient_x,orient_y,orient_z> <FOV>\n" \
	"L <x,y,z> <brightness> <R,G,B>\n" \
	"sp <x,y,z> <diameter> <R,G,B>\n" \
	"pl <x,y,z> <norm_x,norm_y,norm_z> <R,G,B>\n" \
	"cy <x,y,z> <axis_x,axis_y,axis_z> <diameter> <height> <R,G,B>\n"


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
}	t_vec3;

// typedef union u_rgb
// {
// 	uint32_t	rgba;
// 	struct
// 	{
// 		uint8_t	b;
// 		uint8_t	g;
// 		uint8_t	r;
// 		uint8_t	a;
// 	};
// }	t_rgb;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb ;

typedef struct s_light
{
	bool	on;
	double	ratio;
	t_rgb	color;
	t_vec3	pos;
}	t_light;

typedef struct s_cam
{
	bool	on;
	t_vec3	pos;
	t_vec3	forward;
	t_vec3	backward;
	t_vec3	right;
	t_vec3	up;
	int		fov;
	double	viewport_h;
	double	viewport_w;
}	t_cam;

// typedef struct s_light_src
// {
// 	double ratio;
// }	t_light_src;

typedef struct s_sp
{
	double		d;
	double		r;
}	t_sp;

typedef struct s_pl
{
	t_vec3	norm;
}	t_pl;

typedef struct s_cy
{
	t_vec3	norm;
	double		d;
	double		r;
	double		h;
}	t_cy;

typedef struct s_obj
{
	t_obj_type		type;
	t_vec3		pos;
	t_rgb			color;
	void			*shape;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	t_light			amb_light;
	t_light			light;
	t_cam			cam;
	t_obj			**obj_list;
}	t_scene;

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec3	orign;
	t_vec3	dir;
}	t_ray ;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}	t_quad ;

typedef struct s_hit
{
	bool	hit;
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_rgb	color;
}	t_hit ;

typedef struct s_data
{
	t_scene scene;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data ;


// BUG: testing debugging
void		print_scene(t_data *data);
void		print_ray(int x, int y, t_ray ray);
void		print_vec3(t_vec3 vec);
// BUG: END


// mlx
void		destroy_mlx(t_data *data);
void		init_mlx(t_data *data);
void		setup_mlx(t_data *data);
void		img_put_pixel(t_data *data, int x, int y, int color);
int			render_img(t_data *data);

// map pixel
t_ray		map_pixel(int x, int y, t_cam cam);

// camera
void		setup_cam(t_cam *cam);

// hooks
int			handle_keypress(int code, t_data *data);
int			handle_button(int code, int x, int y, t_data *data);

// render
void		draw_image(t_data *data);

// object
void		obj_lst_add(t_obj *obj, t_obj **list);
void		obj_free(t_obj *obj);
void		obj_lst_free(t_obj **obj);

// parse
int			process_line(char *line, t_data *data);
int			parse_file(char *filename, t_data *data);

// error
void		print_error(char *err);
void		exit_error(char *msg, t_data *data);

// exit
int			clean_exit(t_data *data, int status);

// geters
double		get_double(char **line, t_data *data);
t_rgb		get_rgb(char **line, t_data *data);
t_vec3		get_vec3(char **line, t_data *data);
int			get_integer(char **line, t_data *data);

// init
void		init_ambient_light(char *line, t_data *data);
void		init_camera(char *line, t_data *data);
void		init_light(char *line, t_data *data);
void		init_plane(char *line, t_data *data);
void		init_sphere(char *line, t_data *data);
void		init_cylinder(char *line, t_data *data);
void		init_scene(t_data *data);

// vec3 ops
t_vec3		vec3(double x, double y, double z);
t_vec3		vec3_norm(t_vec3 v);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
double		vec3_len(t_vec3 v);
double		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_scale(double s, t_vec3 vec);
t_vec3		vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_negate(t_vec3 v);
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);

// intersect
t_hit		intersect_sp(t_ray ray, t_obj *obj, t_sp *sp, t_data *data);
t_hit		intersect_pl(t_ray ray, t_obj *obj, t_pl *pl, t_data *data);
t_hit		intersect_cy(t_ray ray, t_obj *obj, t_cy *cy, t_data *data);

// intersect utils
void		resolve_hit(t_hit *hit, t_quad quad);
int			check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy);

// hit
t_hit		record_hit(t_obj *obj, t_ray ray, t_data *data);
t_rgb		trace_ray(t_ray ray, t_data *data);

// quadratic
void		solve_quadratic(t_quad *quad);

// color
t_rgb		compute_color(t_hit hit, t_light amb_light, t_light light);
t_rgb		compute_amb(t_rgb color, t_light amb_light);

// rgb ops
t_rgb		rgb(double r, double g, double b);
t_rgb		rgb_add(t_rgb c1, t_rgb c2);
t_rgb		rgb_mult(t_rgb c1, t_rgb c2);
t_rgb		rgb_scale(double k, t_rgb c);
t_rgb		rgb_clamp(t_rgb c);
t_rgb		int_to_rgb(int c);
int			rgb_to_int(t_rgb c);
// utils
bool		is_close(double n, double m);

#endif
