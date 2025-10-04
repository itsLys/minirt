/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:03:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/23 13:18:56 by ihajji           ###   ########.fr       */
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
		mlx_destroy_image(mlx, (*lst)->img.img);
		free((*lst)->name);
		free((*lst)->path);
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}

void	destroy_scene(t_data *data)
{
	free(data->scene.amb.tx_name);
	destroy_objects(data->scene.obj_lst);
	destroy_textures(data->mlx, data->scene.tx_lst);
}

void	destroy_mlx(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}
