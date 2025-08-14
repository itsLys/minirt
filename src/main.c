/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/14 16:09:25 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int clean_exit(int status, t_data *data)
{

	destroy_mlx(data);
	free(data->mlx);
	obj_lst_free(data->scene.obj_list);
	exit(status);
}

void	print_help(void)
{
	int fd;
	int bytes;
	char buff[1024];

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

int main(int ac, char **av)
{
	t_data	data;

	if (0 /* NOTE: implement -h flag */)
		print_help();
	if (ac != 2)
		return print_error("Wrong args\n"), FAILIURE;
	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	print_scene(&data);
	setup_mlx(&data);
	clean_exit(0, &data);
	// printf("Hello\n");
}
