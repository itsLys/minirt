/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:19:43 by ihajji            #+#    #+#             */
/*   Updated: 2025/10/19 15:21:28 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// project name
# define MINIRT_PROJECT "miniRT"

// file extention
# define EXT ".rt"

// windows dimensions
# define WIDTH 1080
# define HEIGHT 720

// pattern defaults
# define PATT_H 512
# define PATT_W 512

// constants
# define SPLIT 24
# define EPS 1e-6
# define CAM_ROTATE_STEP 0.012
# define ROTATE_STEP 0.025
# define MOVE_STEP 0.75
# define FOV_MAX 180.0
# define FOV_MIN 0.0
# define FOV_STEP 1.0
# define RATIO_MAX 1.0
# define RATIO_MIN 0.0
# define RATIO_STEP 0.1
# define DIAMETER_STEP 0.175
# define STRENGTH -1
# define BG_COLOR 0x00202020

# define REF_COEF 1

#endif // !CONSTANTS_H
