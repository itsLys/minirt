/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:32:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/12 16:15:56 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OBJ LIST UTILS
// OBJ ADD,
// OBJ FREE,
// OBJ LST INIT,
// OBJ NEW NOTE,

#include "minirt.h"

void	obj_lst_add(t_obj *obj, t_obj **list)
{
	// printf("lst add obj type:	%d\n", obj->type);
	t_obj *tmp;

	tmp = *list;
	*list = obj;
	// printf("%p\n", tmp);
	obj->next = tmp;
}

void	obj_free(t_obj *obj)
{
	free(obj->shape);
	free(obj);
}

void	obj_lst_free(t_obj **obj)
{
	t_obj *tmp;

	while (*obj)
	{
		tmp = (*obj)->next;
		obj_free(*obj);
		*obj = tmp;
	}
	free(obj);
}

