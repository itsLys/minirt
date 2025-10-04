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

static void	validate_object_texture(t_obj *obj, t_data *data)
{
	if (obj->tx && obj->tx->type != TX_COLOR && obj->tx->type != TX_PATT)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
	if (obj->bmp && obj->bmp->type != TX_BUMP)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
}

static void	find_bmp(t_obj *obj, t_data *data)
{
	t_texture	*bmp;

	bmp = *(data->scene.tx_lst);
	while (bmp)
	{
		if (ft_strcmp(obj->bmp_id, bmp->name) == 0)
		{
			obj->bmp = bmp;
			return ;
		}
		bmp = bmp->next;
	}
}

static void	find_tx(t_obj *obj, t_data *data)
{
	t_texture	*tx;

	tx = *(data->scene.tx_lst);
	while (tx)
	{
		if (ft_strcmp(obj->tx_id, tx->name) == 0)
		{
			obj->tx = tx;
			return ;
		}
		tx = tx->next;
	}
}

void	link_object_texture(t_data *data)
{
	t_obj	*obj;

	obj = *(data->scene.obj_lst);
	while (obj)
	{
		if (obj->type != T_LS && obj->tx_id)
			find_tx(obj, data);
		if (obj->type != T_LS && obj->bmp_id)
			find_bmp(obj, data);
		if (obj->type != T_LS)
			validate_object_texture(obj, data);
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
	if (amb->tx_name)
	{
		if (amb->tx)
			amb->color = rgb_clamp(compute_avg(amb->tx));
		else
			exit_error(ERR_AMB_LIGHT ERR_COULDNT_LOAD, data);
	}
}
