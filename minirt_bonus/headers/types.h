/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:23:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:05:11 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef enum s_obj_type
{
	T_SP,
	T_PL,
	T_CY,
	T_LS,
	T_CN
}	t_obj_type;

typedef enum s_selected_type
{
	T_OBJ,
	T_LIGHT,
	T_CAM
}	t_selected_type;

typedef struct s_vec2
{
	double			x;
	double			y;
}	t_vec2;

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}	t_vec3;

typedef struct s_rgb
{
	double			r;
	double			g;
	double			b;
}	t_rgb;

typedef struct s_light
{
	bool			on;
	double			ratio;
	t_rgb			color;
	t_vec3			pos;
}	t_light;

typedef struct s_cam_rays
{
	t_vec3			**dirs;
	t_vec3			orig;
}	t_cam_rays;

typedef struct s_cam
{
	bool			on;
	t_vec3			pos;
	t_vec3			forward;
	t_vec3			backward;
	t_vec3			right;
	t_vec3			up;
	double			fov;
	double			viewport_h;
	double			viewport_w;
}	t_cam;

typedef struct s_sp
{
	double			d;
	double			r;
}	t_sp;

typedef struct s_pl
{
	t_vec3			norm;
}	t_pl;

typedef struct s_cy
{
	t_vec3			norm;
	double			d;
	double			r;
	double			h;
}	t_cy;

typedef struct s_cn
{
    t_vec3    norm;
    double        angle;
    double        h;
}    t_cn;

typedef struct s_obj
{
	t_obj_type		type;
	t_vec3			pos;
	t_rgb			color;
	void			*shape;
	struct s_obj	*next;
}	t_obj;

typedef struct s_scene
{
	t_light			amb_light;
	t_light			light;
	t_cam			cam;
	t_cam_rays		rays;
	t_obj			**obj_list;
}	t_scene;

typedef struct s_ray
{
	t_vec3			orign;
	t_vec3			dir;
}	t_ray;

typedef struct s_quad
{
	double			a;
	double			b;
	double			c;
	double			t1;
	double			t2;
}	t_quad;

typedef struct s_hit
{
	bool			hit;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_rgb			color;
	t_obj			*obj;
}	t_hit;

typedef struct s_selected
{
	t_selected_type	type;
	t_obj			*obj;
}	t_selected;

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}	t_img;

typedef struct s_data
{
	t_selected		selected;
	t_scene			scene;
	t_vec2			*offsets;
	void			*mlx;
	void			*win;
	t_img			img;
}	t_data;

#endif // !TYPES_H
