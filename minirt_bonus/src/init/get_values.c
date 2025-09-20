/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:12:10 by yel-guad          #+#    #+#             */
/*   Updated: 2025/09/06 16:35:34 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_num(char *str)
{
	int	n;

	n = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str && *str >= '0' && *str <= '9')
		n = (*(str++) - '0') + n * 10;
	return (n);
}

int	get_integer(char **line, t_data *data)
{
	int	n;
	int	i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
	n = parse_num(*line);
	while (ft_isdigit(**line))
	{
		(*line)++;
		i = 1;
	}
	if (i == 0)
		exit_error(ERR_INT, data);
	return (n);
}

char *get_string(char **line, t_data *data)
{
	char	buffer[PATH_MAX];
	char	*str;
	int i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
	if ((**line) == '\n')
		return NULL;
	while (**line && !ft_isspace(**line) && i < PATH_MAX)
	{
		buffer[i++] = **line;
		(*line)++;
	}
	if (i == PATH_MAX)
		return  NULL;
	buffer[i] = 0;
	if (buffer[0] == 0)
		return NULL;
	str = ft_strdup(buffer);
	if (str == NULL)
		exit_error(NULL, data);
	return (str);
}

double	get_double(char **line, t_data *data)
{
	double	f;
	int		i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
	f = ft_atof(*line);
	if (**line == '-' || **line == '+')
		(*line)++;
	while (ft_isdigit(**line))
	{
		(*line)++;
		i = 1;
	}
	if (*(*line) == '.')
		(*line)++;
	while (ft_isdigit(**line))
		(*line)++;
	if (i == 0)
		exit_error(ERR_DBL, data);
	return (f);
}

t_rgb	get_rgb(char **line, t_data *data)
{
	t_rgb	rgb;
	int		tmp;

	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.r = tmp / 255.0;
	if (*(*line)++ != ',')
		exit_error(ERR_RGB, data);
	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.g = tmp / 255.0;
	if (*(*line)++ != ',')
		exit_error(ERR_RGB, data);
	tmp = get_integer(line, data);
	if (tmp > 255)
		exit_error(ERR_RGB, data);
	rgb.b = tmp / 255.0;
	return (rgb);
}

t_vec3	get_vec3(char **line, t_data *data)
{
	t_vec3	vec3;

	vec3.x = get_double(line, data);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS, data);
	vec3.y = get_double(line, data);
	if (*(*line)++ != ',')
		exit_error(ERR_COORDS, data);
	vec3.z = get_double(line, data);
	return (vec3);
}

void	get_texture(t_texture *texture, char **line, t_data *data)
{
	char		*path;

	path = get_string(line, data);
	if (path == NULL)
	{
		texture->ptr = NULL;
		return;
	}
	if (path && path[0] == '/')
		return free(path), exit_error(ERR_TX ERR_REL_PATH, data); //  add freeing of the texture and img destroying
	texture->ptr = mlx_xpm_file_to_image(data->mlx, path, &(texture->width), &(texture->height));
	free(path);
	if (texture->ptr == NULL)
		exit_error("ERR_TEXTURE ERR_COULDNT_LOAD", data);
	texture->addr = mlx_get_data_addr(texture->ptr, &(texture->bpp), &(texture->line_len), &(texture->endian));
	if (texture->addr == NULL)
		exit_error(NULL, data);
}
