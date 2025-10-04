/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:32:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 10:55:06 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	texture_add(t_texture *tx, t_texture **list)
{
	t_texture	*tmp;

	tmp = *list;
	*list = tx;
	tx->next = tmp;
}

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
	if (obj->type != T_LS)
	{
		free(obj->bmp_id);
		free(obj->tx_id);
	}
	free(obj);
}
