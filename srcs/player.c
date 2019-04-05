#include "player.h"
#include "default.h"
#include "config.h"

t_player init_player(t_config *op, t_sector *starting_sector)
{
    t_player p;

    p.vision_height = op->half_h;
    p.heading = EAST;
    p.current_sector = starting_sector;
    p.pos.y = 2;
    p.pos.x = 3;
    p.speed.x = 0;
    p.speed.y = 0;
    p.speed_factor = 1;
    p.jump.ready = t_true;
    p.jump.height = 0;
    p.jump.gravity = 0.93;
    p.jump.duration = 400;
    p.jump.time = 0;
    return (p);
}

void	clamp_player_values(t_player *p, t_config op)
{
    while (p->heading >= CIRCLE)
        p->heading -= CIRCLE;
    while (p->heading < 0)
        p->heading += CIRCLE;
    p->vision_height > op.win_h ? p->vision_height = op.win_h : 0;
    p->vision_height < 0 ? p->vision_height = 0 : p->vision_height;
}