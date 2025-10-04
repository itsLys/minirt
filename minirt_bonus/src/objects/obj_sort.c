/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:09:05 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/20 16:09:32 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	save_content(t_obj *tmp, t_obj *obj)
{
	tmp->type = obj->type;
	tmp->pos = obj->pos;
	tmp->coords = obj->coords;
	tmp->color = obj->color;
	tmp->ref = obj->ref;
	tmp->shine = obj->shine;
	tmp->bmp_id = obj->bmp_id;
	tmp->tx_id = obj->tx_id;
	tmp->tx = obj->tx;
	tmp->tiles = obj->tiles;
	tmp->bmp = obj->bmp;
	tmp->shape = obj->shape;
}

static void	swap_content(t_obj *n1, t_obj *n2)
{
	n1->type = n2->type;
	n1->pos = n2->pos;
	n1->coords = n2->coords;
	n1->color = n2->color;
	n1->ref = n2->ref;
	n1->shine = n2->shine;
	n1->bmp_id = n2->bmp_id;
	n1->tx_id = n2->tx_id;
	n1->tx = n2->tx;
	n1->tiles = n2->tiles;
	n1->bmp = n2->bmp;
	n1->shape = n2->shape;
}

static void	restore_content(t_obj *tmp, t_obj *obj)
{
	obj->type = tmp->type;
	obj->pos = tmp->pos;
	obj->coords = tmp->coords;
	obj->color = tmp->color;
	obj->ref = tmp->ref;
	obj->shine = tmp->shine;
	obj->bmp_id = tmp->bmp_id;
	obj->tx_id = tmp->tx_id;
	obj->tx = tmp->tx;
	obj->tiles = tmp->tiles;
	obj->bmp = tmp->bmp;
	obj->shape = tmp->shape;
}

void	swap_nodes(t_obj **n1, t_obj **n2)// remove from header
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
