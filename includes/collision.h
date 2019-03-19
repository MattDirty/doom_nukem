#ifndef DOOMNUKEM_COLLISION_H
#define DOOMNUKEM_COLLISION_H

#include "utils.h"
#include "walls.h"
#include "sectors.h"

typedef struct          s_collision
{
    double              distance;
    t_coords            inters;
    t_wall				*wall;
}                       t_collision;

t_collision	check_collision(t_sector *sector, t_segment *seg);

#endif