/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:47 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 12:54:24 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "types.h"

// parse parameters
t_texture_type	get_type(char **line, t_data *data);
int				get_integer(char **line, t_data *data);
double			get_double(char **line, t_data *data);
char			*get_string(char **line, t_data *data);
void			get_obj_tx(t_obj *obj, char **line, t_data *data);
void			get_surface_props(t_obj *obj, char *line, t_data *data);
t_vec3			get_vec3(char **line, t_data *data);
t_rgb			get_rgb(char **line, t_data *data);
double          get_double_parameter(char **line, t_data *data);
int             get_integer_parameter(char **line, t_data *data);

// parse textures
void			get_texture(t_texture *tx, char **line, t_data *data);
void			get_image(t_texture *tx, t_data *data);
void			get_pattern(t_texture *tx, char **line, t_data *data);
void			fill_pattern(t_texture *tx, t_rgb c1, t_rgb c2);
void			parse_texture(char *line, t_data *data);

// parse objects
void			parse_light(char *line, t_data *data);
void			parse_cone(char *line, t_data *data);
void			parse_cylinder(char *line, t_data *data);
void			parse_sphere(char *line, t_data *data);
void			parse_plane(char *line, t_data *data);
void            parse_rectangle(char *line, t_data *data);

// parse scene
void			parse_ambient_light(char *line, t_data *data);
void			parse_camera(char *line, t_data *data);

// parse input
int				parse_line(char *line, t_data *data);
int				parse_file(char *filename, t_data *data);

// utils
void			skip_trailing(char *line, t_data *data);
void			init_local_coords(t_obj *obj);
void			check_tx_duplicate(char *name, t_texture *lst, t_data *data);
int				check_file_ext(char *filename);

#endif // !PARSE_H
