/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:58:32 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/27 15:09:45 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_keypress(int code, t_data *data)
{
	(void) data;
	printf("key pressed:	%d\n", code);
	if (code == 65362) // up
		data->scene.cam.pos.z -= 0.05;
	else if (code == 65364) // down
		data->scene.cam.pos.z += 0.05;
	else if (code == 65361) // left
		data->scene.cam.pos.x -= 0.05;
	else if (code == 65363) // right
		data->scene.cam.pos.x += 0.05;
	else if (code == 65365) // PgUp
		data->scene.cam.pos.y += 0.05;
	else if (code == 65366) // PgDn
		data->scene.cam.pos.y -= 0.05;
	mlx_loop_hook(data->mlx, &render_img, data);

	if (code == XK_Escape)
		clean_exit(data, SUCCESS);
	return 0;
}
