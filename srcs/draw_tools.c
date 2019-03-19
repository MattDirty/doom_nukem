#include "default.h"
#include "surface_manipulation.h"

void draw_segment(SDL_Surface *surface, t_segment segment, Uint32 color)
{
    t_i_coords incr;
    int err;
    int cpyerr;
    t_i_coords delta;

    delta.x = ft_abs((int) segment.x2 - (int) segment.x1);
    delta.y = ft_abs((int) segment.y2 - (int) segment.y1);
    incr.x = (int) segment.x1 < (int) segment.x2 ? 1 : -1;
    incr.y = (int) segment.y1 < (int) segment.y2 ? 1 : -1;
    err = (delta.x > delta.y ? delta.x : -delta.y) / 2;
    while ((int) segment.x1 != (int) segment.x2 || (int) segment.y1 != (int) segment.y2)
    {
        if ((int) segment.x1 < 0 || (int) segment.y1 < 0)
            break;
        if ((int) segment.x1 >= surface->w || (int) segment.y1 >= surface->h)
            break;
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
