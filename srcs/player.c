#include "player.h"
#include "default.h"
#include "config.h"

t_player init_player(t_config *op, t_sector *starting_sector)
{
    t_player p;
    
    p.vision_height = op->half_h;
    p.current_sector = starting_sector;
    p.heading = WEST;
    p.pos.y = 2;
    p.pos.x = 3;
    p.speed.x = 0;
    p.speed.y = 0;
    return (p);
}