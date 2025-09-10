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

#include "minirt.h"

void	obj_lst_add(t_obj *obj, t_obj **list)
{
	t_obj	*tmp;

	tmp = *list;
	*list = obj;
	obj->next = tmp;
}

void	obj_free(t_obj *obj)
{
	free(obj->shape);
	free(obj);
}

void	obj_lst_free(t_obj **obj)
{
	t_obj	*tmp;

	while (*obj)
	{
		tmp = (*obj)->next;
		obj_free(*obj);
		*obj = tmp;
	}
	free(obj);
}

void	swap_nodes(t_obj **n1, t_obj **n2)
{
	t_obj	tmp;

	tmp.type = (*n1)->type;
	tmp.pos = (*n1)->pos;
	tmp.color = (*n1)->color;
	tmp.reflect = (*n1)->reflect;
	tmp.shine = (*n1)->shine;
	tmp.shape = (*n1)->shape;
	(*n1)->type = (*n2)->type;
	(*n1)->pos = (*n2)->pos;
	(*n1)->color = (*n2)->color;
	(*n1)->reflect = (*n2)->reflect;
	(*n1)->shine = (*n2)->shine;
	(*n1)->shape = (*n2)->shape;
	(*n2)->type = tmp.type;
	(*n2)->pos = tmp.pos;
	(*n2)->color = tmp.color;
	(*n2)->reflect = tmp.reflect;
	(*n2)->shine = tmp.shine;
	(*n2)->shape = tmp.shape;
}

void	sort_objects(t_obj **head)
{
	t_obj	*tmp;
	t_obj	*node;

	node = *head;
	while (node)
	{
		tmp = node->next;
		while (tmp)
		{
			if (tmp->type < node->type)
				swap_nodes(&tmp, &node);
			tmp = tmp->next;
		}
		node = node->next;
	}
}
