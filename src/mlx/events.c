/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:56:03 by ihajji            #+#    #+#             */
/*   Updated: 2025/08/16 14:17:29 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int mouse_press(int button, int x, int y, void *param)
{
    if (button != 1)          // only care about left click
        return 0;

    t_cam *cam = (t_cam *)param;
    if (!cam) {
        fprintf(stderr, "mouse_press: cam is NULL\n");
        return 0;
    }

    t_ray ray = get_ray(x, y, cam);

    printf("Ray for pixel (%d, %d):\n", x, y);
    printf("Origin    = (%f, %f, %f)\n",
           ray.orign.x, ray.orign.y, ray.orign.z);
    printf("Direction = (%f, %f, %f)\n",
           ray.dir.x, ray.dir.y, ray.dir.z);
    return 0;
}

void	setup_mlx(t_data *data)
{
	init_mlx(data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, &clean_exit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &handle_button, data);
	mlx_loop_hook(data->mlx, &render_img, data);
	mlx_mouse_hook(data->win, mouse_press, &(data->scene.cam));
	mlx_loop(data->mlx);
}
