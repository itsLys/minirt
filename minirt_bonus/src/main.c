/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/10 15:51:30 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clean_exit(t_data *data, int status)
{
	destroy_mlx(data);
	free(data->mlx);
	// join_threads;
	free(data->mapping_workers);
	free(data->render_workers);
	obj_lst_free(data->scene.obj_list);
	if (data->scene.rays.dirs)
		destroy_cam_rays(data->scene.rays);
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
	if (data.scene.cam.on == false)
		exit_error(ERR_CAM ERR_NOT_FOUND, &data);
	if (data.scene.amb_light.on == false)
		exit_error(ERR_AMB_LIGHT ERR_NOT_FOUND, &data);
	if (data.scene.light_on == false)
		exit_error(ERR_LIGHT ERR_NOT_FOUND, &data);
	sort_objects(data.scene.obj_list);
	print_scene(&data);
	init_cam(&data.scene.cam);
	init_offsets(&(data.offsets), &data);
	init_cam_rays(&data);
	// (void) data;
	// void	*mlx_x;
	// void	*win_x;
	// mlx_x = mlx_init();
	// win_x = mlx_new_window(mlx_x, 12, 12, "ewq");
	// printf("%p\n", win_x);
	// exit(321);
	setup_mlx(&data);
	clean_exit(&data, 0);
}
