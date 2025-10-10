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

void	init_surface_props_defaults(t_obj *obj)
{
	if (obj->type == T_PL)
		obj->tiles = (t_int_vec2){10, 10};
	else
		obj->tiles = (t_int_vec2){1, 1};
	obj->tx = NULL;
	obj->bmp = NULL;
}

// TODO: test negative and absurd tiles per axis
void	get_surface_props(t_obj *obj, char *line, t_data *data)
{
	init_surface_props_defaults(obj);
	obj->color = get_rgb(&line, data);
	obj->ref = get_double(&line, data);
	obj->shine = get_integer(&line, data);
	get_obj_tx(obj, &line, data);
	get_obj_tx(obj, &line, data);
	if (obj->tx || obj->bmp)
	{
		obj->tiles.x = get_integer(&line, data);
		obj->tiles.y = get_integer(&line, data);
	}
	if (obj->ref < 0.0 || obj->ref > 1.0)
		exit_error(ERR_WRONG_REF, data);
	if (obj->shine < 1 || obj->shine > 500)
		exit_error(ERR_WRONG_SHINE, data);
	if (obj->tx && (obj->tiles.x < 0 || obj->tiles.y < 0))
		exit_error(ERR_WRONG_TILES, data);
	skip_trailing(line, data);
}
