/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:58:52 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/23 13:07:08 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_string(char **line, t_data *data)
{
	char	buffer[PATH_MAX];
	char	*str;
	int		i;

	i = 0;
	while (ft_isspace(**line))
		(*line)++;
	if ((**line) == '\n' || ft_isdigit(**line))
		return (NULL);
	while (**line && **line != '\n' && !ft_isspace(**line) && i < PATH_MAX)
	{
		buffer[i++] = **line;
		(*line)++;
	}
	if (i == PATH_MAX)
		return (NULL);
	buffer[i] = 0;
	if (buffer[0] == 0)
		return (NULL);
	str = ft_strdup(buffer);
	if (str == NULL)
		exit_error(NULL, data);
	return (str);
}

void	get_obj_tx(t_obj *obj, char **line, t_data *data)
{
	char		*name;
	t_texture	*tx;

	name = get_string(line, data);
	if (name == NULL)
		return ;
	tx = find_tx(name, *(data->scene.tx_lst));
	if (tx == NULL)
		return (free(name), exit_error(ERR_TX_NOT_FOUND, data));
	if (tx->type == TX_BUMP && obj->bmp == NULL)
		obj->bmp = tx;
	else if ((tx->type == TX_COLOR || tx->type == TX_PATT) && obj->tx == NULL)
		obj->tx = tx;
	else if (obj->tx || obj->bmp)
		return (free(name), exit_error(ERR_TYPE_MISS, data));
	free(name);
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
	free(str);
	return (type);
}
