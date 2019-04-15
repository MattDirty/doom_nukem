#include "default.h"
#include "surface_manipulation.h"
#include <math.h>

enum e_bool is_bresenham_out_of_bounds(t_segment *seg, t_i_coords *incr)
{
    if ((incr->x > 0 && (int)seg->x1 > (int)seg->x2)
        || (incr->x < 0 && (int)seg->x1 < (int)seg->x2)
        || (incr->y > 0 && (int)seg->y1 > (int)seg->y2)
        || (incr->y < 0 && (int)seg->y1 < (int)seg->y2))
        return (t_true);
    return (t_false);
}

void draw_segment(SDL_Surface *surface, t_segment segment, Uint32 color)
{
    t_i_coords incr;
    int err;
    int cpyerr;
    t_i_coords delta;

    delta.x = fabs(segment.x2 - segment.x1);
    delta.y = fabs(segment.y2 - segment.y1);
    incr.x = segment.x1 < segment.x2 ? 1 : -1;
    incr.y = segment.y1 < segment.y2 ? 1 : -1;
    err = (delta.x > delta.y ? delta.x : -delta.y) / 2;
    while (((int)segment.x1 != (int)segment.x2
    || (int)segment.y1 != (int)segment.y2)
    && !is_bresenham_out_of_bounds(&segment, &incr))
    {
        if (segment.x1 >= 0 && segment.x1 < surface->w
        && segment.y1 >= 0 && segment.y1 < surface->h)
            put_pixel(surface, (int) segment.x1, (int) segment.y1, color);
        cpyerr = err;
        if (cpyerr > -(delta.x))
        {
            err -= delta.y;
            segment.x1 += incr.x;
        }
        if (cpyerr < delta.y)
        {
            err += delta.x;
            segment.y1 += incr.y;
        }
    }
}

void draw_circle(SDL_Surface *surface, t_coords center, int r, Uint32 color)
{
    int x;
    int y;
    int tx;
    int ty;
    int err;

    x = r - 1;
    y = 0;
    tx = 0;
    ty = 0;
    err = tx - (r << 1);
    while (x >= y)
    {
        put_pixel(surface, center.x + x, center.y - y, color);
        put_pixel(surface, center.x + x, center.y - y, color);
        put_pixel(surface, center.x + x, center.y + y, color);
        put_pixel(surface, center.x - x, center.y - y, color);
        put_pixel(surface, center.x + y, center.y - x, color);
        put_pixel(surface, center.x - x, center.y + y, color);
        put_pixel(surface, center.x - y, center.y + x, color);
        put_pixel(surface, center.x + y, center.y + x, color);
        put_pixel(surface, center.x - y, center.y - x, color);
        if (err <= 0)
        {
            y++;
            err += ty;
            ty += 2;
        }
        if (err > 0)
        {
            x--;
            tx += 2;
            err += tx - (r << 1);
        }
    }
}

void draw_circle_filled(SDL_Surface *surface, t_coords center, int r, Uint32 color)
{
    while (r > 0)
    {
        draw_circle(surface, center, r, color);
        r--;
    }
}
