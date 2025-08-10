/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:04 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/09 12:25:18 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

typedef	struct s_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
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

typedef struct s_light_source
{
	t_coords	pos;
	t_light		light;
}	t_light_source;

typedef struct s_sp
{
	t_coords	pos;
	double		d;
	t_rgb		color;
}	t_sp;

typedef struct s_pl
{
	t_coords	pos;
	t_coords	norm;
	t_rgb		color;
}	t_pl;

typedef struct s_cy
{
	t_coords	pos;
	t_coords	norm;
	double		d;
	double		h;
	t_rgb		color;
}	t_cy;

#endif
