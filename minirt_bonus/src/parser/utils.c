/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:50:31 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/24 13:20:18 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_file_ext(char *filename)
{
	char	*ext;

	ext = ft_strnstr(filename, EXT, ft_strlen(filename));
	if (ext == NULL)
		return (ERROR);
	if (ext[3])
		return (ERROR);
	return (SUCCESS);
}

void	check_tx_duplicate(char *name, t_texture *lst, t_data *data)
{
	while (lst)
	{
		if (ft_strcmp(name, lst->name) == 0)
			exit_error(ERR_TX ERR_DUP_TX, data);
		lst = lst->next;
	}
}

t_texture	*find_tx(char *name, t_texture *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	init_local_coords(t_obj *obj)
{
	t_vec3	tmp_right;

	tmp_right = vec3(1, 0, 0);
	if (is_close(fabs(vec3_dot(tmp_right, obj->coords.up)), 1))
		tmp_right = vec3(0, -1, 0);
	obj->coords.forward = vec3_norm(vec3_cross(obj->coords.up, tmp_right));
	obj->coords.right = vec3_norm(vec3_cross(obj->coords.forward,
				obj->coords.up));
}

void	skip_trailing(char *line, t_data *data)
{
	while (ft_isspace(*line))
		line++;
	if (*line != '\n' && *line != '\0')
		exit_error(ERR_EXTRA_PARAM, data);
}
