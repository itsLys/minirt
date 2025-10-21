/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:23:27 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/19 10:54:54 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stdbool.h>

// enums
typedef enum s_texture_type
{
	TX_INVALID = -1,
	TX_COLOR,
	TX_BUMP,
	TX_PATT
}						t_texture_type;

typedef enum s_obj_type
{
	T_LS,
	T_SP,
	T_PL,
	T_CY,
	T_CN,
	T_RC
}						t_obj_type;

typedef enum s_selected_type
{
	T_OBJ,
	T_LIGHT,
	T_CAM
}						t_selected_type;

// math types
typedef struct s_int_vec2
{
	int					x;
	int					y;
}						t_int_vec2;

typedef struct s_vec2
{
	double				x;
	double				y;
}						t_vec2;

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

typedef struct s_rgb
{
	double				r;
	double				g;
	double				b;
}						t_rgb;

typedef struct s_pixel_neoigh
{
	double				r;
	double				l;
	double				u;
	double				d;
}						t_pixel_neigh;

// img, textures, patterns
typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct s_texture
{
	char				*name;
	char				*path;
	t_texture_type		type;
	t_img				img;
	int					width;
	int					height;
	int					tiles;
	int					strength;
	t_rgb				c1;
	t_rgb				c2;
	struct s_texture	*next;
}						t_texture;

// NOTE: for texture load them from the file
// for pattern, create new image and fill it with the pattern
// planes have a default repeating pattern of N (define)
// other objects have a default of 1
// patterns are intialized in the image in 2*2
// [0,1]
// [1,0]

// typedef struct s_pattern
// {
// 	char				*name;
// 	int					tiles;
// 	t_rgb				c1;
// 	t_rgb				c2;
// 	struct s_pattern	*next;
// }	t_pattern ;

// scene
typedef struct s_local_coords
{
	t_vec3				up;
	t_vec3				right;
	t_vec3				forward;
}						t_local_coords;

typedef struct s_amb_light
{
	bool				on;
	t_rgb				color;
	double				ratio;
	t_texture			*tx;
}						t_amb_light;

typedef struct s_cam_rays
{
	t_vec3				*dirs;
	t_vec3				orig;
}						t_cam_rays;

typedef struct s_cam
{
	bool				on;
	t_vec3				pos;
	t_local_coords		coords;
	double				fov;
	t_vec2				viewport;
	double				viewport_h;
	double				viewport_w;
}						t_cam;

// objects
typedef struct s_light
{
	double				ratio;
}						t_light;
typedef struct s_sp
{
	double				r;
}						t_sp;

typedef struct s_pl
{
}						t_pl;

typedef struct s_rc
{
	double				width;
	double				height;
}						t_rc;

typedef struct s_cy
{
	double				r;
	double				h;
}						t_cy;

typedef struct s_cn
{
	double				angle;
	double				h;
}	t_cn; // make texture mapping for this

// obj, scene

typedef struct s_obj
{
	t_obj_type			type;
	t_local_coords		coords;
	t_vec3				pos;
	t_rgb				color;
	double				ref;
	int					shine;
	double				bmp_strenght;
	t_texture			*bmp;
	t_texture			*tx;
	t_int_vec2			tiles;
	void				*shape;
	struct s_obj		*next;
}	t_obj; // FIX: in sorting

typedef struct s_selected
{
	t_selected_type		type;
	t_obj				*obj;
	t_obj				*light;
}						t_selected;

typedef struct s_scene
{
	bool				light_on;
	t_amb_light			amb;
	t_cam				cam;
	t_selected			selected;
	t_obj				**obj_lst;
	t_texture			**tx_lst;
}						t_scene;

// rays, hit
typedef struct s_ray
{
	t_int_vec2			px;
	t_vec3				orig;
	t_vec3				dir;
}						t_ray;

typedef struct s_quad
{
	double				a;
	double				b;
	double				c;
	double				t1;
	double				t2;
}						t_quad;

typedef struct s_hit
{
	bool				hit;
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_vec3				normal_bumped;
	t_rgb				color;
	t_obj				*obj;
	int					inside;
}						t_hit;

// global data
typedef struct s_data	t_data;

typedef struct s_worker
{
	pthread_t			tid;
	int					number;
	t_int_vec2			start;
	t_int_vec2			end;
	void				(*function)(struct s_worker *);
	t_data				*data;
}						t_worker;

struct					s_data
{
	void				*mlx;
	void				*win;
	int					fd;
	char				*line;
	t_img				img;
	t_scene				scene;
	t_cam_rays			rays;
	t_vec2				*offsets;
	t_worker			*render_workers;
	t_worker			*mapping_workers;
	int					keys[65536];
};

#endif // !TYPES_H
