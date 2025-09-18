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

void	save_content(t_obj *tmp, t_obj *obj)
{
	tmp->type = obj->type;
	tmp->pos = obj->pos;
	tmp->coords = obj->coords;
	tmp->color = obj->color;
	tmp->reflect = obj->reflect;
	tmp->shine = obj->shine;
	tmp->image = obj->image;
	tmp->bumpmap = obj->bumpmap;
	tmp->shape = obj->shape;
}

void	swap_content(t_obj *n1, t_obj *n2)
{
	n1->type = n2->type;
	n1->pos = n2->pos;
	n1->coords = n2->coords;
	n1->color = n2->color;
	n1->reflect = n2->reflect;
	n1->shine = n2->shine;
	n1->image = n2->image;
	n1->bumpmap = n2->bumpmap;
	n1->shape = n2->shape;
}

void	restore_content(t_obj *tmp, t_obj *obj)
{
	obj->type = tmp->type;
	obj->pos = tmp->pos;
	obj->coords = tmp->coords;
	obj->color = tmp->color;
	obj->reflect = tmp->reflect;
	obj->shine = tmp->shine;
	obj->image = tmp->image;
	obj->bumpmap = tmp->bumpmap;
	obj->shape = tmp->shape;
}

void	swap_nodes(t_obj **n1, t_obj **n2)
{
	t_obj	tmp;

	save_content(&tmp, *n1);
	swap_content(*n1, *n2);
	restore_content(&tmp, *n2);
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
