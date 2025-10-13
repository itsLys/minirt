/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:18:13 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 14:53:06 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_sp_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_SP)
	{
		tmp = intersect_sp(ray, *obj, (t_sp *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_pl_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_PL)
	{
		tmp = intersect_pl(ray, *obj, (t_pl *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_cy_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_CY)
	{
		tmp = intersect_cy(ray, *obj, (t_cy *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_cn_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_CN)
	{
		tmp = intersect_cn(ray, *obj, (t_cn *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}

void	check_rc_intersect(t_obj **obj, t_hit *hit, t_ray ray)
{
	t_hit	tmp;

	while (*obj && (*obj)->type == T_RC)
	{
		tmp = intersect_rc(ray, *obj, (t_rc *)((*obj)->shape));
		if (tmp.hit && tmp.t < hit->t)
		{
			*hit = tmp;
			hit->color = (*obj)->color;
			hit->obj = *obj;
		}
		(*obj) = (*obj)->next;
	}
}
