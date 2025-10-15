/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:35:54 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 14:51:13 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "types.h"

void	check_sp_intersect(t_obj **obj, t_hit *hit, t_ray ray);
void	check_pl_intersect(t_obj **obj, t_hit *hit, t_ray ray);
void	check_cy_intersect(t_obj **obj, t_hit *hit, t_ray ray);
void	check_cn_intersect(t_obj **obj, t_hit *hit, t_ray ray);
void	check_rc_intersect(t_obj **obj, t_hit *hit, t_ray ray);
t_hit	intersect_sp(t_ray ray, t_obj *obj, t_sp *sp);
t_hit	intersect_pl(t_ray ray, t_obj *obj, t_pl *pl);
t_hit	intersect_cy(t_ray ray, t_obj *obj, t_cy *cy);
t_hit	intersect_cn(t_ray ray, t_obj *obj, t_cn *cn);
t_hit	intersect_rc(t_ray ray, t_obj *obj, t_rc *rc); // new
t_hit	resolve_pl_hit(t_ray ray, t_obj *obj, double a, double b);
t_hit	resolve_cy_hit(t_ray ray, t_obj *obj, t_cy *cy, t_quad quad);
t_hit	resolve_sp_hit(t_ray ray, t_obj *obj, t_sp *sp, t_quad quad);
t_hit	resolve_cn_hit(t_ray ray, t_obj *obj, t_quad quad, t_cn *cn);
t_hit	resolve_rc_hit(t_ray ray, t_obj *obj, double a, double b);
void	resolve_hit(t_hit *hit, t_quad quad);
void	solve_quadratic(t_quad *quad);

// utils
bool	check_cn_height_intersect(double t, t_ray ray, t_obj *obj, t_cn *cn);
bool	check_cy_height_intersect(double t, t_ray ray, t_obj *obj, t_cy *cy);
bool	check_rc_height_length(t_obj *obj, t_vec3 hitpoint);

#endif // !INTERSECT_H
