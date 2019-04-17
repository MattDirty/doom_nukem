#ifndef DOOMNUKEM_HORIZONTAL_MOTION_H
# define DOOMNUKEM_HORIZONTAL_MOTION_H

#include "utils.h"
#include "sectors.h"

t_coords	allowed_move(t_vector speed, t_coords position, t_sector **current_sector);

#endif
