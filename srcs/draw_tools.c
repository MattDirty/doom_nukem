#include "default.h"
#include "surface_manipulation.h"
#include <math.h>

enum e_bool is_bresenham_finished(t_segment *seg, t_i_coords *incr)
{
    if ((incr->x > 0 && (int)seg->x1 > (int)seg->x2)
        || (incr->x < 0 && (int)seg->x1 < (int)seg->x2)
        || (incr->y > 0 && (int)seg->y1 > (int)seg->y2)
        || (incr->y < 0 && (int)seg->y1 < (int)seg->y2))
        return (e_true);
    return (e_false);
}

void draw_segment(SDL_Surface *surface, t_segment s, Uint32 color)
{
    t_i_coords incr;
    int err;
    int cpyerr;
    t_i_coords delta;

    delta = (t_i_coords){fabs(s.x2 - s.x1), fabs(s.y2 - s.y1)};
    incr = (t_i_coords){s.x1 < s.x2 ? 1 : -1, s.y1 < s.y2 ? 1 : -1};
    err = (delta.x > delta.y ? delta.x : -delta.y) / 2;
    while (((int)s.x1 != (int)s.x2 || (int)s.y1 != (int)s.y2)
    && !is_bresenham_finished(&s, &incr))
    {
        if (s.x1 >= 0 && s.x1 < surface->w && s.y1 >= 0 && s.y1 < surface->h)
            put_pixel(surface, (int) s.x1, (int) s.y1, color);
        cpyerr = err;
        if (cpyerr > -(delta.x))
        {
            err -= delta.y;
            s.x1 += incr.x;
        }
        if (cpyerr < delta.y)
        {
            err += delta.x;
            s.y1 += incr.y;
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
        if ((center.x - r) >= 0 && (center.x + r) < surface->w
            && (center.y - r) >= 0 && (center.y + r) < surface->h)
            draw_circle(surface, center, r, color);
        r--;
    }
}
