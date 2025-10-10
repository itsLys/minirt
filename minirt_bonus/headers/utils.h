/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:42:02 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/06 15:28:40 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

bool	is_close(double n, double m);
bool	greater_than(double n, double m);
bool	is_less_then(double n, double m);
void	print_error(char *err);
int		clean_exit(t_data *data, int status);
void	exit_error(char *msg, t_data *data);
#endif // !UTILS_H
