#ifndef DOOMNUKEM_DEFAULT_H
# define DOOMNUKEM_DEFAULT_H

#include "libft.h"

# define CONFIG_PATH "config.ini"

# define DEBUG_W 800
# define DEBUG_H 640
# define DEBUG_W_H (DEBUG_W / 2)
# define DEBUG_H_H (DEBUG_H / 2)
# define DEBUG_GRID_STEP 40
# define DEBUG_ZOOM 20

# define GRID_COLOR 0xFF111111
# define ABS_ORD_COLOR 0xFFE2EAFF
# define DEBUG_WALL_COLOR 0xFFFFFFFF
# define DEBUG_PORTAL_COLOR 0xFFFF0000
# define DEBUG_PLAYER_COLOR 0xFF4FE4EA

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
# define RUN 0.001
# define ROT_X 0.001
# define ROT_Y 1
# define MOUSE_SENSI 0.0001

# define ACTIVATE_LIGHTING 1

# define MAX_SLOT_USABLE 3

#endif
