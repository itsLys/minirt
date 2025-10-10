/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:35:54 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/08 12:08:17 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "types.h"

t_hit	intersect_sp(t_ray ray, t_obj *obj, t_sp *sp);
t_hit	intersect_pl(t_ray ray, t_obj *obj, t_pl *pl);
t_hit	intersect_cy(t_ray ray, t_obj *obj, t_cy *cy);
t_hit	intersect_cn(t_ray ray, t_obj *obj, t_cn *cn);
t_hit	resolve_pl_hit(t_ray ray, t_obj *obj, double a, double b);
t_hit	resolve_cy_hit(t_ray ray, t_obj *obj, t_cy *cy, t_quad quad);
t_hit	resolve_sp_hit(t_ray ray, t_obj *obj, t_sp *sp, t_quad quad);
t_hit	resolve_cn_hit(t_ray ray, t_obj *obj, t_quad quad, t_cn *cn);
void	resolve_hit(t_hit *hit, t_quad quad);
void	solve_quadratic(t_quad *quad);

#endif // !INTERSECT_H
