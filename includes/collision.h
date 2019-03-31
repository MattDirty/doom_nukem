#ifndef COLLISION_H
# define COLLISION_H

# include "utils.h"
# include "walls.h"
# include "sectors.h"
# include "doom.h"

typedef struct          s_collision
{
    double              distance;
    double              wall_length;
    t_coords            inters;
    t_wall				*wall;
}                       t_collision;

t_collision	check_collision(t_sector *sector, t_segment *seg);
void		raycasting(t_env *e);

#endif