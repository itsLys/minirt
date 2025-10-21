/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:04:10 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/20 16:04:17 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	validate_scene(t_scene scene, t_data *data)
{
	if (scene.cam.on == false)
		exit_error(ERR_CAM ERR_NOT_FOUND, data);
	if (scene.amb.on == false)
		exit_error(ERR_AMB_LIGHT ERR_NOT_FOUND, data);
	if (scene.light_on == false)
		exit_error(ERR_LIGHT ERR_NOT_FOUND, data);
}

void	prepare_scene(t_data *data)
{
	validate_scene(data->scene, data);
	init_offsets(&(data->offsets), data);
	init_cam_rays(data);
	sort_objects(data->scene.obj_lst);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("Wrong args\n"), FAILIURE);
	if (ac == 2 && ft_strcmp(av[1], "-h") == 0)
		return (print_help(), SUCCESS);
	if (init_program(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	prepare_scene(&data);
	print_scene(&data);
	mlx_loop(data.mlx);
}
