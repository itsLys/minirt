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
# define ERR_LIGHT "Light: "
# define ERR_PARAM "Wrong parameter field\n"

// ERR PARAMS
# define ERR_RGB "RGB is not correct\n"
# define ERR_DIAM_POS "Diameter must be >= 0\n"
# define ERR_HEIGHT "Height must be >= 0\n"
# define ERR_DBL "Double is not correct\n"
# define ERR_INT "Integer is not correct\n"
# define ERR_RATIO "Ratio is not correct\n"
# define ERR_NORM_VAL "Normalized value is not correct\n"
# define ERR_FOV "Fov is not correct\n"
# define ERR_COORDS "Wrong coordination form!\n"
# define ERR_EXTRA_PARAM "Unrecognized parameter!\n"
# define ERR_MULTI "Can only be declared once!\n"
# define ERR_NOT_FOUND "Parameter not found!\n"

# define ERR_EXT "Wrong file extension\n"
// ERR USAGE
# define ERR_USAGE " \
	`./minirt -h` for help\n \
	A <ratio> <R,G,B>\n \
	C <x,y,z> <orient_x,orient_y,orient_z> <FOV>\n \
	L <x,y,z> <brightness> <R,G,B>\n \
	sp <x,y,z> <diameter> <R,G,B>\n \
	pl <x,y,z> <norm_x,norm_y,norm_z> <R,G,B>\n \
	cy <x,y,z> <axis_x,axis_y,axis_z> <diameter> <height> <R,G,B>\n"

#endif // !ERROR_H
