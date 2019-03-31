#ifndef ENGINE_H
# define ENGINE_H

# include "doom.h"
# include "collision.h"

void		raycasting(t_env *e);
void		draw(t_env *e, double ray_angle, t_collision collision, Uint32 renderer_x);
t_sector	*get_next_sector_addr(t_sector *current, t_wall *wall);

#endif
