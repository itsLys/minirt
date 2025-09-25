/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:20:23 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/25 15:46:19 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	assign_object_texture(t_obj *obj, t_texture *tx)
{
	if (tx->type == TX_COLOR || tx->type == TX_PATT)
		obj->tx = tx;
}

static void	validate_object_texture(t_obj *obj, t_data *data)
{
	if (obj->tx && obj->tx->type != TX_COLOR && obj->tx->type != TX_PATT)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
	if (obj->bmp && obj->bmp->type != TX_BUMP)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
}

static void	find_texture(t_obj *obj, t_data *data)
{
	t_texture	*tx;

	tx = *(data->scene.tx_lst);
	while (tx)
	{
		if (obj->tx_id_1 && ft_strcmp(obj->tx_id_1, tx->name) == 0)
			assign_object_texture(obj, tx);
		if (obj->tx_id_2 && ft_strcmp(obj->tx_id_2, tx->name) == 0)
			obj->bmp = tx;
		validate_object_texture(obj, data);
		tx = tx->next;
	}
}

void	link_object_texture(t_data *data)
{
	t_obj	*obj;

	obj = *(data->scene.obj_lst);
	while (obj)
	{
		if (obj->type != T_LS)
			find_texture(obj, data);
		obj = obj->next;
	}
}

void	link_amb_texture(t_data *data)
{
	t_texture	*tx;
	t_amb_light	*amb;

	tx = *(data->scene.tx_lst);
	amb = &(data->scene.amb);
	while (tx)
	{
		if (amb->tx_name && ft_strcmp(amb->tx_name, tx->name) == 0)
		{
			amb->tx = tx;
			break ;
		}
		tx = tx->next;
	}
	if (amb->tx)
		amb->color = rgb_clamp(compute_avg(amb->tx));
}
