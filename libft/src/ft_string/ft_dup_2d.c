/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:01:54 by ihajji            #+#    #+#             */
/*   Updated: 2025/06/10 13:02:21 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_dup_2d(char **env)
{
	int i;
	char **dup;

	i = 0;
	while (env[i])
		i++;

	dup = malloc(sizeof(char *) * (i + 1));
	if (dup == NULL)
		return NULL;
	i = 0;
	while (env[i])
	{
		dup[i] = ft_strdup(env[i]);
		if (dup[i] == NULL)
			return (char **) ft_free_vector(dup);
		i++;
	}
	dup[i] = NULL;
}
