/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badhont <badhont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 00:56:09 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/10 19:20:04 by badhont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include "SDL.h"
#include "e_bool.h"
#include "doom.h"

Uint32  get_pixel(SDL_Surface *s, int x, int y, enum e_bool force_alpha)
{
    Uint8 *pix;
    Uint32 color;

    pix = s->pixels + (x + y * s->w) * 4;
    color =  *pix << 24 | *(pix + 3) << 16 | *(pix + 2) << 8 | *(pix + 1);
    if (force_alpha)
        color |= 0xff000000;
    return (color);
}

void    put_pixel(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;

    pix = s->pixels;
    pix[x + y * s->w] = color;
}

void    put_pixel_alpha(SDL_Surface *s, int x, int y, Uint32 color)
{
    Uint32 *pix;
    Uint32 alpha;
    Uint32 rb;
    Uint32 g;

    alpha = (color & 0xff000000) >> 24;
    if (alpha == 0)
        return;
    if (0 && alpha == 0xff)
    {
        pix = s->pixels;
        pix[x + y * s->w] = color;
        return;
    }
    pix = (Uint32*)s->pixels + x + y * s->w;
    rb = ((0x100 - alpha) * (*pix & 0xff00ff)) >> 8
        | (alpha * (color & 0xff00ff)) >> 8;
    g  = ((0x100 - alpha) * (*pix & 0x00ff00)) >> 8
        | (alpha * (color & 0x00ff00)) >> 8;
    *pix = 0xff000000 | (rb & 0xff00ff) | (g & 0x00ff00);
}

void        rotate_and_draw(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos, enum e_bool force_alpha)
{
    int x;
    int y;

    x = 0;
    while (x < text->w)
    {
        y = text->h - 1;
        while (y >= 0)
        {
            put_pixel_alpha(surface, pos.x + y, pos.y + x,
                            get_pixel(text, x, y, force_alpha));
            y--;
        }
        x++;
    }

}

void        draw_on_screen(SDL_Surface *surface, SDL_Surface *text, t_i_coords pos, enum e_bool force_alpha)
{
    int x;
    int y;

    y = 0;
    while (y < text->h)
    {
        x = 0;
        while (x < text->w)
        {
            if (pos.x + x < surface->w && pos.y + y < surface->h)
                put_pixel_alpha(surface, pos.x + x, pos.y + y,
                            get_pixel(text, x, y, force_alpha));
            x++;
        }
        y++;
    }
}

void    print_surface(SDL_Renderer *renderer, SDL_Surface *surface)
{
    SDL_Texture *texture;

    if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
        error_doom("error: cannot create texture");
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}
