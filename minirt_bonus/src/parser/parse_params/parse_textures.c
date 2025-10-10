/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:45:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 11:31:47 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_pattern(t_texture *tx, t_rgb c1, t_rgb c2)
{
	int			i;
	int			j;
	t_int_vec2	sq_size;
	t_int_vec2	sq;
	t_rgb		color;

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
			img_put_pixel(tx->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	get_pattern(t_texture *tx, char **line, t_data *data)
{
	tx->c1 = get_rgb(line, data);
	tx->c2 = get_rgb(line, data);
	tx->height = PATT_H;
	tx->width = PATT_W;
	tx->img.img = mlx_new_image(data->mlx, tx->width, tx->height);
	if (tx->img.img == NULL)
		exit_error(NULL, data);
	tx->img.addr = mlx_get_data_addr(tx->img.img, &(tx->img.bpp),
			&(tx->img.line_len), &(tx->img.endian));
	if (tx->img.addr == NULL)
		exit_error(NULL, data);
	fill_pattern(tx, tx->c1, tx->c2);
}

// FIX: add freeing of the texture and img destroying
void	get_image(t_texture *tx, t_data *data)
{
	if (tx->path && tx->path[0] == '/')
		exit_error(ERR_TX ERR_REL_PATH, data);
	tx->img.img = mlx_xpm_file_to_image(data->mlx, tx->path, &(tx->width),
			&(tx->height));
	if (tx->img.img == NULL)
		exit_error(ERR_TX ERR_COULDNT_LOAD, data);
	tx->img.addr = mlx_get_data_addr(tx->img.img, &(tx->img.bpp),
			&(tx->img.line_len), &(tx->img.endian));
	if (tx->img.addr == NULL)
		exit_error(NULL, data);
}

// FIX: free at exit
void	get_texture(t_texture *tx, char **line, t_data *data)
{
	if (tx->type == TX_PATT)
		get_pattern(tx, line, data);
	else if (tx->type == TX_BUMP || tx->type == TX_COLOR)
	{
		tx->path = get_string(line, data);
		if (tx->path == NULL)
			exit_error(ERR_TX ERR_REL_PATH, data);
		get_image(tx, data);
	}
}

// FIX: add name freeing at exit
void	parse_texture(char *line, t_data *data)
{
	t_texture	*tx;
	t_texture	*lst;

	lst = *(data->scene.tx_lst);
	tx = malloc(sizeof(t_texture));
	if (tx == NULL)
		return (exit_error(NULL, data));
	texture_add(tx, data->scene.tx_lst);
	tx->name = get_string(&line, data);
	check_tx_duplicate(tx->name, lst, data);
	tx->type = get_type(&line, data);
	if (tx->type == TX_INVALID)
		exit_error(ERR_TX ERR_TX_TYPE, data);
	get_texture(tx, &line, data);
	skip_trailing(line, data);
}
