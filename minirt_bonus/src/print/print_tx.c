/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:46:30 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/11 10:02:57 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_texture_type(t_texture *lst)
{
	if (lst->type == TX_COLOR)
		printf("color");
	else if (lst->type == TX_BUMP)
		printf("bump");
	else if (lst->type == TX_PATT)
		printf("patt");
}

void	print_textures(t_texture *lst)
{
	while (lst)
	{
		printf("t	");
		printf("%s			", lst->name);
		print_texture_type(lst);
		if (lst->type == TX_PATT)
		{
			printf("%d, %d, %d		",
				(int)(lst->c1.r * 255.999),
				(int)(lst->c1.g * 255.999),
				(int)(lst->c1.b * 255.999));
			printf("%d, %d, %d		",
				(int)(lst->c2.r * 255.999),
				(int)(lst->c2.g * 255.999),
				(int)(lst->c2.b * 255.999));
		}
		printf("	%s			", lst->path);
		printf("\n");
		lst = lst->next;
	}
}
