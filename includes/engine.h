#ifndef DOOMNUKEM_ENGINE_H
#define DOOMNUKEM_ENGINE_H

#include "collision.h"

void		raycasting(t_env *e);
void		draw(t_env *e, double ray_angle, t_collision collision, Uint32 renderer_x);

#endif
