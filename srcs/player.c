#include "doom.h"

void init_player(t_player *p)
{
    p->vision_height = HALF_H;
    p->heading = WEST;
    p->pos.y = 2;
    p->pos.x = 3;
    p->speed.x = 0;
    p->speed.y = 0;
//    p->weapons = load_weapons();
}