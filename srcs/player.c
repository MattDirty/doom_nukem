#include "player.h"
#include "default.h"
#include "config.h"

t_player init_player(t_config *op)
{
    t_player p;
    
    p.vision_height = op->half_h;
    p.heading = EAST;
    p.pos.y = 2;
    p.pos.x = 3;
    p.speed.x = 0;
    p.speed.y = 0;
    return (p);
}