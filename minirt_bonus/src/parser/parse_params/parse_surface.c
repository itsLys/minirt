/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_surface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:01:21 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/23 13:01:53 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_surface_props(t_obj *obj, char *line, t_data *data)
{
	obj->color = get_rgb(&line, data);
	obj->ref = get_double(&line, data);
	obj->shine = get_integer(&line, data);
	get_obj_tx(obj, &line, data);
	if (obj->ref < 0.0 || obj->ref > 1.0)
		exit_error(ERR_WRONG_REF, data);
	if (obj->shine < 0 || obj->shine > 200)
		exit_error(ERR_WRONG_SHINE, data);
	obj->tx = NULL;
	obj->bmp = NULL;
	skip_trailing(line, data);
}
