#include "default.h"
#include "ui.h"
#include "utils.h"
#include "surface_manipulation.h"

void    draw_crosshair(SDL_Surface *surface, Uint32 color)
{
    t_segment   segment;

    segment.x1 = HALF_W;
    segment.y1 = HALF_H - 30;
    segment.x2 = HALF_W;
    segment.y2 = HALF_H - 30 - 50;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W - 30;
    segment.y1 = HALF_H;
    segment.x2 = HALF_W - 30 - 50;
    segment.y2 = HALF_H;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W;
    segment.y1 = HALF_H + 30;
    segment.x2 = HALF_W;
    segment.y2 = HALF_H + 30 + 50;
    draw_segment(surface, segment, color);
    segment.x1 = HALF_W + 30;
    segment.y1 = HALF_H;
    segment.x2 = HALF_W + 30 + 50;
    segment.y2 = HALF_H;
    draw_segment(surface, segment, color);
    put_pixel_alpha(surface, HALF_W, HALF_H, color);
}

void    ui_draw(t_sdl *sdl)
{
    draw_crosshair(sdl->surface, CROSSHAIR_COLOR);
}