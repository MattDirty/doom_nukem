#include "libft.h"
#include "default.h"
#include "ui.h"
#include "utils.h"
#include "surface_manipulation.h"
#include "config.h"
#include "map.h"

static void     draw_crosshair(SDL_Surface *surface, t_config *op, Uint32 color)
{
    t_segment   segment;

    segment.x1 = op->half_w;
    segment.y1 = op->half_h - 30;
    segment.x2 = op->half_w;
    segment.y2 = op->half_h - 30 - 50;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w - 30;
    segment.y1 = op->half_h;
    segment.x2 = op->half_w - 30 - 50;
    segment.y2 = op->half_h;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w;
    segment.y1 = op->half_h + 30;
    segment.x2 = op->half_w;
    segment.y2 = op->half_h + 30 + 50;
    draw_segment(surface, segment, color);
    segment.x1 = op->half_w + 30;
    segment.y1 = op->half_h;
    segment.x2 = op->half_w + 30 + 50;
    segment.y2 = op->half_h;
    draw_segment(surface, segment, color);
    put_pixel_alpha(surface, op->half_w, op->half_h, color);
}

static void     draw_fps(SDL_Surface *surface, int fps, t_config *op)
{
    SDL_Surface *fps_text;
    t_coords    location;

    location.x = 10;
    location.y = 10;
    if (location.x >= op->win_w)
        location.x = 0;
    if (location.y >= op->win_h)
        location.y = 0;
    fps_text = write_text("fonts/sixty.ttf", 20, ft_strjoin(ft_itoa(fps), " fps"), (SDL_Colour){255,255,255,255});
    draw_on_screen(surface, fps_text, location, t_false);
    free(fps_text);
}

static void     draw_health(SDL_Surface *surface, t_player *p, t_map *map, t_config *op)
{
    SDL_Surface *health;
    t_coords    location;

    location.x = op->half_w - 250;
    location.y = op->win_h - 45;
    if (location.x < 0)
        location.x = 0;
    if (location.y < 0)
        location.y = 0;
    health = write_text("fonts/sixty.ttf", 40, ft_itoa(p->health), (SDL_Colour){244, 182, 66, 255});
    draw_on_screen(surface, health, location, t_false);
    location.x = op->half_w - 300;
    location.y = op->win_h - 50;
    if (location.x < 0)
        location.x = 0;
    if (location.y < 0)
        location.y = 0;
    if (map->i > 2 || p->dead)
        map->i = 0;
    draw_on_screen(surface, map->cross[map->i], location, t_false);
    free(health);
}

void            draw_ammo(SDL_Surface *surface, SDL_Surface *bullet, Uint32 ammo, t_config *op)
{
    SDL_Surface *ammo_nb;
    t_coords     location;

    location.x = op->half_w + 250;
    location.y = op->win_h - 45;
    if (location.x >= op->win_w)
        location.x = op->half_w;
    if (location.y < 0)
        location.y = 0;
    ammo_nb = write_text("fonts/sixty.ttf", 40, ft_itoa(ammo), (SDL_Colour){0, 0, 0, 255});
    draw_on_screen(surface, ammo_nb, location, t_false);
    location.x = op->half_w + 285;
    location.y = op->win_h - 52;
    if (location.x >= op->win_w)
        location.x = op->half_w;
    if (location.y < 0)
        location.y = 0;
    draw_on_screen(surface, bullet, location, t_false);
    free(ammo_nb);
}

void            ui_draw(SDL_Surface *surface, t_map *map, int fps, t_env *e)
{
    draw_crosshair(surface, &e->op, CROSSHAIR_COLOR);
    draw_fps(surface, fps, &e->op);
    draw_sun_or_moon(surface, map, &e->op);
    draw_health(surface, &e->p, map, &e->op);
    draw_ammo(surface, map->bullet, e->p.weapons.list[e->p.weapons.current].ammo, &e->op);
}

