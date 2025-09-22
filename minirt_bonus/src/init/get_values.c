/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:12:10 by yel-guad          #+#    #+#             */
/*   Updated: 2025/09/21 10:21:18 by ihajji           ###   ########.fr       */
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

t_texture_type	get_type(char **line, t_data *data)
{
	char			*str;
	t_texture_type	type;

	str = get_string(line, data);
	if (str == NULL)
		exit_error(NULL, data);
	if (ft_strcmp("bump", str) == 0)
		type = TX_BUMP;
	else if (ft_strcmp("color", str) == 0)
		type = TX_COLOR;
	else if (ft_strcmp("patt", str) == 0)
		type = TX_PATT;
	else
		type = TX_INVALID;
	return type;
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
	int		i;

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

#define PATT_H 512
#define PATT_W 512

void	init_pattern(t_texture *tx, t_rgb c1, t_rgb c2)
{
	int i;
	int j;
	t_int_vec2 sq_size;
	t_int_vec2 sq;
	t_rgb	color;

	sq_size.x = tx->width / 2;
	sq_size.y = tx->height / 2;
	i = 0;
	while (i < tx->width)
	{
		j = 0;
		while (j < tx->height)
		{
			sq.x = i / sq_size.x;
			sq.y = j / sq_size.y;
			if ((sq.x + sq.y) % 2 == 0)
				color = c1;
			else
				color = c2;
			img_put_pixel(tx->img, i, j, rgb_to_int(color));
			j++;
		}
		i++;
	}
}

void	get_pattern(t_texture *tx, char **line, t_data *data)
{
	t_rgb c1;
	t_rgb c2;

	c1 = get_rgb(line, data);
	c2 = get_rgb(line, data);
	tx->height = PATT_H;
	tx->width = PATT_W;
	tx->tiles = 50; // MAKE A MECHANISM BY WHICH YOU INCREASE THE NUMBER OF THESE
	tx->img.img = mlx_new_image(data->mlx, tx->width, tx->height);
	if (tx->img.img == NULL)
		exit_error(NULL, data);
	tx->img.addr  = mlx_get_data_addr(tx->img.img, &(tx->img.bpp), &(tx->img.line_len), &(tx->img.endian));
	if (tx->img.addr == NULL)
		exit_error(NULL, data);
	init_pattern(tx, c1, c2);
}

void	get_image(t_texture *tx, char **line, t_data *data)
{
	char *path;

	path = get_string(line, data);
	if (path == NULL)
		exit_error(ERR_TX ERR_REL_PATH, data);
	if (path && path[0] == '/')
		return free(path), exit_error(ERR_TX ERR_REL_PATH, data); //  add freeing of the texture and img destroying
	tx->img.img = mlx_xpm_file_to_image(data->mlx, path, &(tx->width), &(tx->height));
	free(path);
	if (tx->img.img == NULL)
		exit_error("ERR_TEXTURE ERR_COULDNT_LOAD", data);
	tx->img.addr = mlx_get_data_addr(tx->img.img, &(tx->img.bpp), &(tx->img.line_len), &(tx->img.endian));
	if (tx->img.addr == NULL)
		exit_error(NULL, data);
}

void	get_texture(t_texture *tx, char **line, t_data *data)
{
	if (tx->type == TX_PATT)
		get_pattern(tx, line, data);
	else if (tx->type == TX_BUMP || tx->type == TX_COLOR)
		get_image(tx, line, data);
}
