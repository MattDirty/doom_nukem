/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:39:43 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/12 05:41:06 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

# include "libft.h"

# define CONFIG_PATH "config.ini"

# define CROSSHAIR_COLOR 0xE400FF00

# define FPS_MAX 60

# define WIN_W 800
# define WIN_H 640
# define HALF_W ((double)WIN_W / 2)
# define HALF_H ((double)WIN_H / 2)

# define FULLSCREEN t_false

# define FOV 90.0
# define HALF_FOV (FOV / 2)
# define HORIZON 25
# define TAN_HALF_FOV (tan(ft_degtorad(HALF_FOV)))
# define RATIO (HALF_W / TAN_HALF_FOV)

# define MASK_ALPHA 0xFF000000
# define MASK_RED 0x00FF0000
# define MASK_GREEN 0x0000FF00
# define MASK_BLUE 0x000000FF

# define BLACK 0xFF000000
# define WHITE 0xFFFFFFFF

# define EAST 0
# define CIRCLE 6.28319
# define ROT_90 1.5708

# define RAD_DEG_100 1.74533
# define RAD_DEG_80 1.39626

# define PLAYER_THICKNESS 0.25
# define JUMP_MAX 50
# define HEALTH_MAX 100
# define DAMAGE 2
# define HEAL 1

# define RUN 0.001
# define ROT_X 0.001
# define ROT_Y 1
# define MOUSE_SENSI 0.0001

# define ACTIVATE_LIGHTING 1

#endif
