/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:42:45 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:43:19 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "types.h"

void		obj_lst_add(t_obj *obj, t_obj **list);
void		obj_free(t_obj *obj);
void		obj_lst_free(t_obj **obj);
void		swap_nodes(t_obj **n1, t_obj **n2);
void		sort_objects(t_obj **head);

#endif // !OBJECTS_H
