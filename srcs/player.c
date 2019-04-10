#include "player.h"
#include "default.h"
#include "config.h"
#include "ui.h"

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
    p.jump.gravity = 0.1;
    p.jump.duration = 400;
    p.jump.time = 0;
    p.dead = t_false;
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

void    game_over(SDL_Surface *surface, t_config *op)
{
    SDL_Surface *game_over;
    t_coords    location;

    game_over = write_text("fonts/horrendo.ttf", 120, "GAME OVER!", (SDL_Colour){255,0,0,255});
    location.x = op->half_w - game_over->w / 2;
    location.y = op->half_h - game_over->h / 2;
    draw_on_screen(surface, game_over, location, t_false);
    free(game_over);
}