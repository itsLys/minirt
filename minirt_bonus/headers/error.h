/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:22:12 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 16:26:09 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ERR OBJS
# define ERR_AMB_LIGHT "Ambient: "
# define ERR_CAM "Camera: "
# define ERR_CY "Cylinder: "
# define ERR_SP "Sphere: "
# define ERR_PL "Plane: "
# define ERR_CN "Cone: "
# define ERR_LIGHT "Light: "
# define ERR_PARAM "Wrong parameter field\n"
# define ERR_TX "Texture: "

// ERR PARAMS
# define ERR_RGB "RGB is not correct\n"
# define ERR_DIAM_POS "Diameter must be 0\n"
# define ERR_DBL "Double is not correct\n"
# define ERR_INT "Integer is not correct\n"
# define ERR_RATIO "Ratio is not correct\n"
# define ERR_NORM_VAL "Normalized value is not correct\n"
# define ERR_FOV "Fov is not correct\n"
# define ERR_COORDS "Wrong coordination form!\n"
# define ERR_EXTRA_PARAM "Unrecognized parameter!\n"
# define ERR_MULTI "Can only be declared once!\n"
# define ERR_NOT_FOUND "Parameter not found!\n"
# define ERR_WRONG_REF "Wrong reflectivness\n"
# define ERR_WRONG_SHINE "Wrong shininess\n"
# define ERR_REL_PATH "Invalid relative path\n"
# define ERR_COULDNT_LOAD "Coulnd't load texture\n"
# define ERR_TX_TYPE "Wrong texture type\n"
# define ERR_DUP_TX "Duplicated texture\n"
# define ERR_TYPE_MISS "Texture type missmatch\n"
# define ERR_WRONG_TILES "Wrong tiles per axis\n"

# define ERR_USAGE " \
	`./minirt -h` for help\n \
	A	<ratio> <R,G,B> [<texture_name>]\n \
	C	<x,y,z> <orient_x,orient_y,orient_z> <FOV>\n \
	l	<x,y,z> <brightness> <R,G,B>\n \
																\
	t	<texture_name> <color/bump> <texture_relative_path>\n \
	t	<texture_name> <patt> <R,G,B> <R,G,B>\n \
\
	sp	<x,y,z> <north_x,north_y,north_z> <seam_x,seam_y,seam_z> <diameter> <R,G,B> <reflectivness> <shininess> [<texture/pattern name> <bumpmap_name>]\n \
	pl	<x,y,z> <face_x,face_y,face_z> <R,G,B> <reflectivness> <shininess> [<texture/pattern name> <bumpmap_name>] \n \
	cy	<x,y,z> <axis_x,axis_y,axis_z> <diameter> <height> <R,G,B> <reflectivness> <shininess> <texture/pattern name>\n \
	cn	<x,y,z> <axis_x,axis_y,axis_z> <angle> <height> <R,G,B> <reflectivness> <shininess> <texture/pattern name>\n \
	"
// TODO: orientation and axis don't have to be normalized, normalize them at parse time
	// if number of tiles is not given, assume  a default
#endif // !ERROR_H
