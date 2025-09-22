/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:03:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/20 16:06:17 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	 destroy_workers(t_data *data)
{
	join_threads(data->mapping_workers, SPLIT * SPLIT);
	join_threads(data->render_workers, SPLIT * SPLIT);
	free(data->mapping_workers);
	free(data->render_workers);
}

void	destroy_objects(t_obj **lst)
{
	t_obj	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->type != T_LS)
		{
			free((*lst)->tx_id_1); // FIX: free after initialization, maybe not for printing??
			free((*lst)->tx_id_2);
		}
		obj_free(*lst);
		*lst = tmp;
	}
	free(lst);
}

void	destroy_textures(void *mlx, t_texture **lst)
{
	t_texture	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		mlx_destroy_image(mlx, (*lst)->img.img);
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}

void	destroy_scene(t_data *data)
{
	destroy_objects(data->scene.obj_lst);
	destroy_textures(data->mlx, data->scene.tx_lst);
}
