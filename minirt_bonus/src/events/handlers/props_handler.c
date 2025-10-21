/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:07:22 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/16 10:46:43 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_cy_props(int code, t_cy *cy)
{
	if (code == XK_equal)
		cy->r = cy->r + DIAMETER_STEP;
	else if (code == XK_minus)
		cy->r = fmax(cy->r - DIAMETER_STEP, 0.0);
	else if (code == XK_m)
		cy->h = cy->h + DIAMETER_STEP;
	else if (code == XK_n)
		cy->h = fmax(cy->h - DIAMETER_STEP, 0.0);
}

void	handle_cn_props(int code, t_cn *cn)
{
	if (code == XK_equal)
		cn->angle = cn->angle + DIAMETER_STEP;
	else if (code == XK_minus)
		cn->angle = fmax(cn->angle - DIAMETER_STEP, 0.0);
	else if (code == XK_m)
		cn->h = cn->h + DIAMETER_STEP;
	else if (code == XK_n)
		cn->h = fmax(cn->h - DIAMETER_STEP, 0.0);
	if (fabs(fmod(cn->angle, 360.0)) == 180.0)
		cn->angle = cn->angle - 1;
}

void	handle_sp_props(int code, t_sp *sp)
{
	if (code == XK_equal)
		sp->r = sp->r + DIAMETER_STEP;
	else if (code == XK_minus)
		sp->r = fmax(sp->r - DIAMETER_STEP, 0.0);
}

void	handle_rc_props(int code, t_rc *rc)
{
	if (code == XK_equal)
		rc->width = rc->width + DIAMETER_STEP;
	else if (code == XK_minus)
		rc->width = fmax(rc->width - DIAMETER_STEP, 0.0);
	else if (code == XK_m)
		rc->height = rc->height + DIAMETER_STEP;
	else if (code == XK_n)
		rc->height = fmax(rc->height - DIAMETER_STEP, 0.0);
	if (fabs(fmod(rc->width, 360.0)) == 180.0)
		rc->width = rc->width - 1;
}
