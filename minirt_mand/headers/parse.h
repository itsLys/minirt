/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajji <ihajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:38:47 by ihajji            #+#    #+#             */
/*   Updated: 2025/09/05 10:39:24 by ihajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "types.h"

int			process_line(char *line, t_data *data);
int			parse_file(char *filename, t_data *data);
double		get_double(char **line, t_data *data);
t_rgb		get_rgb(char **line, t_data *data);
t_vec3		get_vec3(char **line, t_data *data);
int			get_integer(char **line, t_data *data);
double      get_double_parameter(char **line, t_data *data);
int         parse_num(char *str);


#endif // !PARSE_H
