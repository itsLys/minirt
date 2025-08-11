/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:09:09 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/10 15:41:54 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EXT ".rt"

int	check_file_ext(char *filename)
{
	char	*ext;

	ext = ft_strnstr(filename, EXT, ft_strlen(filename)); 
	if (ext == NULL)
		return ERROR;
	if (ext[3])
		return ERROR;
	return SUCCESS;
}

void print_error(char *err)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, err, ft_strlen(err));
}

int	parse_file(char *filename, t_data *data)
{
	int	fd;

	if (check_file_ext(filename) == ERROR)
		return ERROR;
	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		return print_error(strerror(errno)), ERROR;

	char *line;

	
	while (1)
	{
		line = get_next_line(fd);
		while (ft_strisempty(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (line == NULL)
			break;
		if (process_line(line, data) == ERROR)
			return ERROR;
		free(line);
	}
}

int main(int ac, char **av)
{
	t_data	data;

	if (parse_file(av[1], &data) == ERROR)
		return (EXIT_FAILURE);
}
