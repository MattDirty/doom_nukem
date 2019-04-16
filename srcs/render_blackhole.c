#include "render_blackhole.h"

void    put_pixel_blackhole(t_env *e, int x, int y, Uint32 color)
{
    Uint32 *pix;
    Uint32 alpha;
    Uint32 rb;
    Uint32 g;

    alpha = (color & 0xff000000) >> 24;
    if (alpha == 0)
        return;
    if (e->p.health < rand() % 100)
    {
#ifdef BLACKHOLE_LSD
        return;
#else
        pix = e->doom.surface->pixels;
        pix[x + y * e->doom.surface->w] = 0xff000000;
        return;
#endif
    }
    if (alpha == 0xff)
    {
        pix = e->doom.surface->pixels;
        pix[x + y * e->doom.surface->w] = color;
        return;
    }
    pix = (Uint32*)e->doom.surface->pixels + x + y * e->doom.surface->w;
    rb = ((0x100 - alpha) * (*pix & 0xff00ff)) >> 8
        | (alpha * (color & 0xff00ff)) >> 8;
    g  = ((0x100 - alpha) * (*pix & 0x00ff00)) >> 8
        | (alpha * (color & 0x00ff00)) >> 8;
    *pix = 0xff000000 | (rb & 0xff00ff) | (g & 0x00ff00);
}
