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

void	assign_texture(t_obj *obj, t_texture *tx)
{
	if (tx->type == BUMP_TX)
		obj->tx.bmp = tx;
	else if (tx->type == COLOR_TX)
		obj->tx.tx = tx;
}

void	find_texture(t_obj *obj, t_data *data)
{
	char		*name;
	t_texture	*tx;

	tx = *(data->scene.tx_lst);
	while (tx)
	{
		name = tx->name;
		if (obj->tx.ids[0] && tx_exists(name, data) && ft_strcmp(obj->tx.ids[0], name) == 0)
			assign_texture(obj, tx);
		if (obj->tx.ids[1] && tx_exists(name, data) && ft_strcmp(obj->tx.ids[1], name) == 0)
			assign_texture(obj, tx);
	}
}

void	assign_object_textures(t_data *data)
{
	t_texture	*tx;
	t_pattern	*patt;
	t_obj *obj = *(data->scene.obj_lst);

	while (obj)
	{
		find_texture(obj, data);
	}


	// for each object
	// check it's name (both)
	// find it in the texture and  pattern list
	// assign the texture struct to the object texture
	// if and object has two same textures ==> error
	// if an object has pattern and texture ==> error
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
	assign_object_textures(&data);
	setup_mlx(&data);
	clean_exit(&data, 0);
}
