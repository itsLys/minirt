/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:03:40 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/13 15:02:09 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_workers(t_data *data)
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
		if ((*lst)->img.img)
			mlx_destroy_image(mlx, (*lst)->img.img);
		free((*lst)->path);
		free((*lst)->name);
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}

void	destroy_scene(t_data *data)
{
	if (data->scene.amb.tx && data->scene.amb.tx->img.img)
		mlx_destroy_image(data->mlx, data->scene.amb.tx->img.img);
	if (data->scene.amb.tx && data->scene.amb.tx->path)
		free(data->scene.amb.tx->path);
	free(data->scene.amb.tx);
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
