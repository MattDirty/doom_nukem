#include "libft.h"
#include "default.h"
#include "ui.h"
#include "utils.h"
#include "surface_manipulation.h"
#include "config.h"
#include "map.h"

static void draw_crosshair(SDL_Surface *surface, t_config *op, Uint32 color)
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

void draw_fps(SDL_Surface *surface, int fps, t_config *op)
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

void        draw_sun_or_moon(SDL_Surface *surface, t_map *map, t_config *op)
{
    t_coords    location;

    location.x = op->win_w - 50;
    location.y = 0;
    if (map->daytime)
        draw_on_screen(surface, map->sun, location, t_true);
    else
        draw_on_screen(surface, map->moon, location, t_true);
}

void        ui_draw(t_sdl *sdl, t_config *op)
{
    draw_crosshair(sdl->surface, op, CROSSHAIR_COLOR);
}