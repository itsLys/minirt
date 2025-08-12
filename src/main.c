/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/12 20:11:50 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return print_error("Wrong args\n"), FAILIURE;
	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
	print_scene(&data);
	clean_exit(&data);
	printf("Hello\n");
}
