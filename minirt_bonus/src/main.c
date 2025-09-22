/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/21 12:27:39 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
int	clean_exit(t_data *data, int status)
{
	destroy_mlx(data);
	destroy_workers(data);
	destroy_scene(data);
	obj_lst_free(data->scene.obj_lst);
	if (data->rays.dirs)
		free(data->rays.dirs);
	if (data->offsets)
		free(data->offsets);
	exit(status);
}

void	print_help(void)
{
	int		fd;
	int		bytes;
	char	buff[1024];

	bytes = -1;
	fd = open("rules.txt", O_RDONLY);
	if (fd == ERROR)
		return ;
	while (bytes != 0)
	{
		bytes = read(fd, buff, 1023);
		buff[bytes] = '\0';
		printf("%s", buff);
	}
	close(fd);
}

void	validate_scene(t_data *data, t_scene scene)
{
	if (scene.cam.on == false)
		exit_error(ERR_CAM ERR_NOT_FOUND, data);
	if (scene.amb.on == false)
		exit_error(ERR_AMB_LIGHT ERR_NOT_FOUND, data);
	if (scene.light_on == false)
		exit_error(ERR_LIGHT ERR_NOT_FOUND, data);
}

void	assign_object_texture(t_obj *obj, t_texture *tx)
{
	if (tx->type == TX_COLOR || tx->type == TX_PATT)
		obj->tx = tx;
}

void	validate_object_texture(t_obj *obj, t_data *data)
{
	if (obj->tx && obj->tx->type != TX_COLOR && obj->tx->type != TX_PATT)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
	if (obj->bmp && obj->bmp->type != TX_BUMP)
		exit_error(ERR_TX ERR_TYPE_MISS, data);
}

void	find_texture(t_obj *obj, t_data *data)
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
		find_texture(obj, data);
		obj = obj->next;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac >= 2 && ft_strcmp(av[1], "-h") == 0)
		print_help();
	if (ac != 2)
		return (print_error("Wrong args\n"), FAILIURE);
	init_data(&data);
	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	validate_scene(&data, data.scene);
	print_scene(&data); // FIX: print textures, patterns, and new fields
	sort_objects(data.scene.obj_lst); // FIX: add missing fields in swapping
	init_offsets(&(data.offsets), &data);
	init_cam_rays(&data);
	link_object_texture(&data);
	setup_mlx(&data);
	clean_exit(&data, 0);
}
