/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/31 16:34:25 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int clean_exit(t_data *data, int status)
{
	destroy_mlx(data);
	free(data->mlx);
	obj_lst_free(data->scene.obj_list);
	destroy_cam_rays(data->scene.rays);
	free(data->offsets);
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

void	init_offsets(t_vec2	**offsets, t_data *data)
{
	double px;
	double py;
	int i = 0;
	int j;
	*offsets = malloc(sizeof(t_vec2) * WIDTH * HEIGHT);
	// malloc fails?

	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			px = (i + 0.5) / WIDTH;
			py = (j + 0.5) / HEIGHT;
			px = (px - 0.5) * data->scene.cam.viewport_w;
			py = (0.5 - py) * data->scene.cam.viewport_h;
			(*offsets)[j * WIDTH + i].x = px;
			(*offsets)[j * WIDTH + i].y = py;
			j++;
		}
		i++;
	}
}

void	swap_nodes(t_obj **n1, t_obj **n2)
{
	t_obj	tmp;

	tmp.type = (*n1)->type;
	tmp.pos = (*n1)->pos;
	tmp.color = (*n1)->color;
	tmp.shape = (*n1)->shape;
	(*n1)->type = (*n2)->type;
	(*n1)->pos = (*n2)->pos;
	(*n1)->color = (*n2)->color;
	(*n1)->shape = (*n2)->shape;
	(*n2)->type = tmp.type;
	(*n2)->pos = tmp.pos;
	(*n2)->color = tmp.color;
	(*n2)->shape = tmp.shape;
}

void	sort_objects(t_obj **head)
{
	// head == 123;
	t_obj	*tmp;
	t_obj	*node;

	node = *head;
	while (node)
	{
		tmp = node->next;
		while (tmp)
		{
			if (tmp->type < node->type)
				swap_nodes(&tmp, &node);
			tmp = tmp->next;
		}
		node = node->next;
	}
}

int main(int ac, char **av)
{
	t_data	data;
	if (0 /* NOTE: implement -h flag */)
		print_help();
	if (ac != 2)
		return print_error("Wrong args\n"), FAILIURE;
	init_data(&data);
	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	if (data.scene.cam.on == false)
		exit_error(ERR_CAM ERR_NOT_FOUND, &data);
	if (data.scene.amb_light.on == false)
		exit_error(ERR_AMB_LIGHT ERR_NOT_FOUND, &data);
	if (data.scene.light.on == false)
		exit_error(ERR_LIGHT ERR_NOT_FOUND, &data);
	sort_objects(data.scene.obj_list);
	print_scene(&data);
	init_cam(&data.scene.cam);
	init_offsets(&(data.offsets), &data);
	init_cam_rays(&data);
	setup_mlx(&data);
	clean_exit(&data, 0);
	// printf("Hello\n");
}
