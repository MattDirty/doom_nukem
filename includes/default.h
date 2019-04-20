/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:34:07 by badhont           #+#    #+#             */
/*   Updated: 2019/04/19 02:34:39 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

# include "libft.h"

# define CROSSHAIR_COLOR 0xE400FF00

# define FPS_MAX 300

# define WIN_W 1920
# define WIN_H 1080
# define HALF_W ((double)WIN_W / 2)
# define HALF_H ((double)WIN_H / 2)

# define FULLSCREEN e_false

# define FOV 90.0
# define HALF_FOV (FOV / 2)
# define HORIZON 100
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
# define AMMO_MAX 30
# define BLACKHOLE_AURA_DAMAGE 1

# define MS_TO_S 0.001
# define ROT_X 0.001
# define ROT_Y 1
# define MOUSE_SENSI 0.0001

# define EPSILON 0.0001

# define ACTIVATE_LIGHTING 1

#endif
